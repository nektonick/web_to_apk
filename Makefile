ANDROID="/usr/lib/android-sdk/platforms/android-23/android.jar"
MANIFEST="app/AndroidManifest.xml"

test:
	echo app/*
	echo app/%

commit:
	git add --a
	git commit
	git push origin master

make_r:
	aapt package -f -m -J app/src -M ${MANIFEST} -S app/res -I ${ANDROID}

compile: make_r
	javac -source 8 -target 8 -d app/obj -classpath app/src -bootclasspath ${ANDROID} app/src/com/example/helloandroid/*.java
	
classes: compile
	dx --dex --output=app/bin/classes.dex app/obj

build: classes
	aapt package -f -m -F app/bin/unaligned.apk -M ${MANIFEST} -S app/res -I ${ANDROID}
	cd app/bin/; aapt add unaligned.apk classes.dex

apk: build
	java -jar uber-apk-signer-0.8.4.jar -a app/bin/unaligned.apk -o app/bin
	mv app/bin/unaligned-aligned-debugSigned.apk app/bin/finished.apk

install: apk
	adb install app/bin/finished.apk

clean:
	rm -f app/bin/*
	rm -f app/obj/com/example/helloandroid/*
	rm -f app/src/com/example/helloandroid/R.java
