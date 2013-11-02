;
#import "ViewController.h"
#import "NSData+Base64.h"
#include "CPFInterface.h"
#import "CiOSPlatform.h"

#ifdef USE_EXTERNAL_SDK_LOVELIVE
#import "SDKWrapper.h"
#endif

@implementation ViewController

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Release any cached data, images, etc that aren't in use.
}

NSMutableDictionary* transactionDict =[NSMutableDictionary dictionary];
#pragma mark - View lifecycle

// 回転を検出した際に呼び出される
- (void) willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
    CPFInterface& pfif = CPFInterface::getInstance();
    if(!pfif.isClient()) return;
    CGRect f = self.view.frame;
    int width = f.size.width * [UIScreen mainScreen].scale;
    int height = f.size.height * [UIScreen mainScreen].scale;
    // 縦位置か横位置かを検出
    if(UIInterfaceOrientationIsPortrait(toInterfaceOrientation)) {
        // 縦位置
        pfif.client().changeScreenInfo(IClientRequest::LEFT_TOP, width, height);
    } else {
        // 横位置
        pfif.client().changeScreenInfo(IClientRequest::LEFT_TOP, height, width);        
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    if(![SKPaymentQueue canMakePayments]) {
        UIAlertView * alert = [[UIAlertView alloc] initWithTitle:@"課金制限"
                                                         message:@"設定によりアプリ内課金が制限されています。"
                                                        delegate:nil
                                               cancelButtonTitle:nil
                                               otherButtonTitles:@"OK", nil];
        [alert show];
        [alert release];
    }
        
    [UIApplication sharedApplication].statusBarHidden = YES;
    [self.view setFrame:[[UIScreen mainScreen] bounds]];
    self.view.contentScaleFactor = [UIScreen mainScreen].scale;
    [viewGL startAnimation];
    [viewGL setViewController:self];

	// Do any additional setup after loading the view, typically from a nib.
#ifdef USE_EXTERNAL_SDK_LOVELIVE
    [SDKWrapper onLoad];
#endif
}
- (void)viewDidUnload
{
    [viewGL stopAnimation];
//    [self setViewBase:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
}

- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
}

// 実際ローテーションされた場合に呼び出される。
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    IClientRequest::SCRMODE mode;

    switch(interfaceOrientation)
    {
        case UIInterfaceOrientationPortrait:
        case UIInterfaceOrientationPortraitUpsideDown:
            mode = IClientRequest::PORTRAIT;
            break;
        case UIInterfaceOrientationLandscapeLeft:
        case UIInterfaceOrientationLandscapeRight:
            mode = IClientRequest::LANDSCAPE;
            break;
    }

    CPFInterface& pfif = CPFInterface::getInstance();
    //if(!pfif.isClient()) {
        return (mode == IClientRequest::LANDSCAPE) ? YES : NO;
    //}
    return pfif.client().reportScreenRotation(IClientRequest::LEFT_TOP, mode) ? YES : NO;
}

- (void)viewRecovery
{
    [viewGL setTimePrev:0];
}

- (void)stopAnimation
{
    [viewGL stopAnimation];
}

- (void)startAnimation
{
    [viewGL startAnimation];
}

-(void)clearUITouches
{
    [viewGL clearUITouches];
}

- (void)dealloc {
    [viewBase release];
    [super dealloc];
}

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response {
  if([response.invalidProductIdentifiers count] > 0)
    {
      // アイテムIDが不正
      IClientRequest& cli = CPFInterface::getInstance().client();
      for (NSString* product_id in response.invalidProductIdentifiers)
        {
          const char* utf8_id = [product_id UTF8String];
          if (!utf8_id)
            {
              utf8_id = "";
            }
          size_t len = strlen(utf8_id) + 1;
          cli.controlEvent(IClientRequest::E_STORE_BAD_ITEMID,
                           0,
                           len,
                           (void*)utf8_id,
                           0,
                           0);
          CPFInterface::getInstance().platform().logging("[store] invalid item id: %s.",
                                                         utf8_id);
        }
    }

  // Platformを取得して処理を振り分ける.
  CiOSPlatform* Platform(CiOSPlatform::getInstance());
  if (Platform)
    {
      Platform->responseStoreKitProducts(response, self);
    }
}

- (void)finishStoreTransaction:(NSString *)receipt
{
	SKPaymentTransaction * transaction = [transactionDict objectForKey:receipt];
    if (transaction) {
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    
        [transactionDict removeObjectForKey:receipt];
    
#ifdef USE_EXTERNAL_SDK_LOVELIVE
        [SDKWrapper onPayment:transaction];
#endif
    } else {
      /* oh hell.. we are doomed */
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue removedTransactions: (NSArray *)transactions {
  @synchronized(self) {
    [[NSUserDefaults standardUserDefaults] setBool: NO
                                             forKey:@"PaymentTransactionBool"];
    [[NSUserDefaults standardUserDefaults] synchronize];
  }
}

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions {
    
    IClientRequest& cli = CPFInterface::getInstance().client();
    
    for(SKPaymentTransaction * transaction in transactions) {
        NSString * productId = transaction.payment.productIdentifier;
        const char * utf8_id = [productId UTF8String];
        size_t len = strlen(utf8_id) + 1;

        switch (transaction.transactionState) {
            case SKPaymentTransactionStatePurchasing: {
              // 購入処理中
              @synchronized(self){
                [[NSUserDefaults standardUserDefaults] setBool:YES
                                                        forKey:@"PaymentTransactionBool"];
                [[NSUserDefaults standardUserDefaults] synchronize];
              }
                cli.controlEvent(IClientRequest::E_STORE_PURCHASHING, 0, len, (void *)utf8_id, 0, 0);
                break;
            }
            case SKPaymentTransactionStatePurchased: {
                // 購入処理成功
                
                // レシート情報を取得する
                NSString * receipt = [transaction.transactionReceipt base64EncodedString];
                const char * utf8_receipt = [receipt UTF8String];
                size_t len_receipt = strlen(utf8_receipt) + 1;
                
                cli.controlEvent(IClientRequest::E_STORE_PURCHASHED, 0,
                                 len, (void *)utf8_id, len_receipt, (void *)utf8_receipt);

                [transactionDict setObject:transaction forKey:[NSString stringWithFormat:@"%s", utf8_receipt]];
                break;
            }
            case SKPaymentTransactionStateFailed: {
              // 購入処理エラーもしくはキャンセル
              switch ([transaction.error code])
                {
                case SKErrorUnknown:
                  {
                  }
                  break;
                case SKErrorClientInvalid:
                  {
                  }
                  break;
                case SKErrorPaymentCancelled:
                  {
                  }
                  break;
                case SKErrorPaymentInvalid:
                  {
                  }
                  break;
                case SKErrorPaymentNotAllowed:
                  {
                  }
                  break;
                case SKErrorStoreProductNotAvailable:
                  {
                  }
                  break;
                default:
                  {
                  }
                  break;
                }
                cli.controlEvent(IClientRequest::E_STORE_FAILED, 0, len, (void *)utf8_id, 0, 0);
                [queue finishTransaction:transaction];
                break;
            }
            case SKPaymentTransactionStateRestored: {
                // アイテムのリストア(購入済みアイテムの再付与(再インストール等で最6初から持っている状態にすべき、など)完了
                // ラブライブでは非消費型アイテムは扱わないのでこの遷移に入る事は無い - yukishita
                cli.controlEvent(IClientRequest::E_STORE_RESTORE, 0, len, (void *)utf8_id, 0, 0);
                [queue finishTransaction:transaction];
                break;
            }
            default: break; // unreachable
        }
    }
}

- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error {
    // リストア失敗
    // ラブライブでは非消費型アイテムは扱わないのでこの遷移に入る事は無い - yukishita
    IClientRequest& cli = CPFInterface::getInstance().client();
    cli.controlEvent(IClientRequest::E_STORE_RESTORE_FAILED, 0, 0, 0, 0, 0);
}

- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue {
    // 全リストア終了
    // ラブライブでは非消費型アイテムは扱わないのでこの遷移に入る事は無い - yukishita
    IClientRequest& cli = CPFInterface::getInstance().client();
    cli.controlEvent(IClientRequest::E_STORE_RESTORE_COMPLETED, 0, 0, 0, 0, 0);
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    abort();
}
@end
