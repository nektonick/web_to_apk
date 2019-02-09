commit:
	git add --a
	git commit
	git push origin master

make_r:
	cd app
	pwd
	export ANDROID=/usr/lib/android-sdk/platforms/android-23/android.jar
	echo $ANDROID
	aapt package -f -m -J src -M AndroidManifest.xml -S res -I $ANDROID

compile: make_r
	javac -source 8 -target 8 -d obj -classpath src -bootclasspath $ANDROID src/com/example/helloandroid/*.java
	
classes: compile
	dx --dex --output=bin/classes.dex obj

build: classes
	aapt package -f -m -F bin/unaligned.apk -M AndroidManifest.xml -S res -I $ANDROID
	cp bin/classes.dex .
	aapt add bin/unaligned.apk classes.dex
	rm classes.dex

apk: build
	java -jar ../uber-apk-signer-0.8.4.jar -a bin/unaligned.apk -o bin

install: apk
	adb install bin/unaligned-aligned-debugSigned.apk

clean:
	bash clean.sh
