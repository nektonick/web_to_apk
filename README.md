## Сборка приложения (для Ubuntu x64)
#### Установка зависимостей
```
sudo add-apt-repository ppa:maarten-fonville/android-build-tools
sudo apt update
sudo apt insatll git adb default-jdk android-build-tools-installer android-sdk-platform-23
```
#### Загрузка файлов
```
git clone https://github.com/nektonick/web_to_apk
cd web_to_apk/app
export ANDROID=/usr/lib/android-sdk/platforms/android-23/android.jar
```
#### Создание `R.java` файла
```
aapt package -f -m -J src -M AndroidManifest.xml -S res -I $ANDROID
```
#### Компиляция
```
javac -source 8 -target 8 -d obj -classpath src -bootclasspath $ANDROID src/com/example/helloandroid/*.java
```
#### Сборка `classes.dex` файла
```
dx --dex --output=bin/classes.dex obj
```
#### Сборка пакета
```
aapt package -f -m -F bin/unaligned.apk -M AndroidManifest.xml -S res -I $ANDROID
cp bin/classes.dex .
aapt add bin/unaligned.apk classes.dex 
rm classes.dex
```
#### Подпись и выравнивание
```
java -jar ../uber-apk-signer-0.8.4.jar -a bin/unaligned.apk -o bin
```
#### Установка приложения
```
adb install bin/unaligned-aligned-debugSigned.apk
```
