# Toboggan の使い方

## for Mac

wineを使っても、monoを使っても、GUIを使うのは無理です！

以下の手順で、他のプラットフォームで用意したリソースを利用可能な形式に変更することはできるようになります。
https://docs.google.com/document/d/1BcnOGfAbiPY7T2yoxAwWdwAyuOOwaZLvejUbVtwMyzw/edit#

手順を簡略化するため、上記セットアップを行うスクリプトを用意しました。
`$ ./mac-setup.sh` を実行してください。

あとは `mono ~/path/to/Toboggan/KLBToolHost.exe --verbose --clean --publish --force --all-profiles --directory .` とかで動くと思います。
