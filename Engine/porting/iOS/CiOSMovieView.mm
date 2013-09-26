/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
//
//  CiOSMovieView.mm
//  GameEngine
//
//

#import "CiOSMovieView.h"
#include "CiOSWidget.h"
@implementation CiOSMovieView

+ (Class)layerClass
{
    return [AVPlayerLayer class];
}

- (void)playerItemDidReachEnd:(NSNotification *)notification
{
    AVPlayerItem * p = [notification object];
    CiOSMovieWidget * pWidget = CiOSMovieWidget::getWidget(p);
    
    if(!pWidget) return;
    pWidget->setStatus(1);  // 終了ステータスを書き込む
    // movie play end
}

@end
