# set params
ANDROID_NDK_ROOT=/cygdrive/e/android-ndk-r5
COCOS2DX_ROOT=/cygdrive/d/Work7/cocos2d-x
TESTS_ROOT=$COCOS2DX_ROOT/tests/test.android

# make sure assets is exist
if [ -d $TESTS_ROOT/assets ]; then
    rm -rf $TESTS_ROOT/assets
fi

mkdir $TESTS_ROOT/assets

# copy resources
for file in $COCOS2DX_ROOT/tests/Res/*
do
    if [ -d $file ]; then
        cp -rf $file $TESTS_ROOT/assets
    fi

    if [ -f $file ]; then
        cp $file $TESTS_ROOT/assets
    fi
done


# build
pushd $ANDROID_NDK_ROOT
./ndk-build -C $TESTS_ROOT $*
popd

