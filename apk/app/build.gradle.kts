plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.android)
}

android {
    namespace = "app.zlangjit"
    compileSdk = 34

    defaultConfig {
        applicationId = "app.zlangjit"
        minSdk = 28 // Android Pie
        targetSdk = 34
        versionCode = GRADLE_VERSION_CODE
        versionName = "GRADLE_VERSION_STRING"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    signingConfigs {
        create("release") {
            storeFile = file("keystore")
            storePassword = "123456"
            keyAlias = "keystore"
            keyPassword = "123456"
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            isDebuggable = false
            isJniDebuggable = false
            isPseudoLocalesEnabled = false
            signingConfig = signingConfigs.getByName("release")
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_17
        targetCompatibility = JavaVersion.VERSION_17
    }
    kotlinOptions {
        jvmTarget = "17"
    }
    
    packagingOptions {
        jniLibs {
            useLegacyPackaging true
        }
    }
    
    buildFeatures {
        viewBinding = true
        buildConfig = true
        prefab = true
    }
    externalNativeBuild {
        cmake {
            path = file("../../CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)
    implementation(libs.androidx.games.activity)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)
}
