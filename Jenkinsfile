pipeline {
  agent none
  stages {
    stage('Build') {
      parallel {
        stage('Build macOS') {
          agent {
            node {
              label 'macos'
            }
          }
          steps {
            sh '''
               # Setup environment
               export PATH="/usr/local/bin:$PATH"

               # Get dependencies (we force it on macOS/Linux because of CMake/Ninja issue)
               mkdir -p build_deps
               cd build_deps
               cmake ../Source/GetDeps -G "Ninja"
               ninja
               cd ..
            '''
            sh '''
               # Setup environment
               export PATH="/usr/local/bin:$PATH"

               # Build Release
               mkdir -p build
               cd build
               cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
               ninja
               cd ..
            '''
          }
          post {
            success {
              deploy();
            }
          }
        }
        stage('Build Windows x64') {
          agent {
            node {
              label 'win_x64'
            }
          }
          steps {
            bat '''
               rem Setup environment
               call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" amd64
               set CC=cl.exe
               set CXX=cl.exe

               rem Build Release
               if not exist build mkdir build
               cd build
               cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=MinSizeRel
               ninja
               cd ..
            '''
          }
          post {
            success {
              deploy();
            }
          }
        }
        stage('Build Windows x64 UWP') {
          agent {
            node {
              label 'win10_x64'
            }
          }
          steps {
            bat '''
               rem Setup environment
               call "C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Community\\VC\\Auxiliary\\Build\\vcvarsall.bat" amd64 uwp
               set CC=cl.exe
               set CXX=cl.exe

               rem Build Release
               if not exist build mkdir build
               cd build
               cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release -DUWP_PLATFORM=1 -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0
               ninja
               cd ..
            '''
          }
          post {
            success {
              deploy();
            }
          }
        }
        stage('Build Linux') {
          agent {
            node {
              label 'linux'
            }
          }
          steps {
            sh '''
               # Get dependencies (we force it on macOS/Linux because of CMake/Ninja issue)
               mkdir -p build_deps
               cd build_deps
               cmake ../Source/GetDeps -G "Ninja"
               ninja
               cd ..
            '''
            sh '''     
               # Build Release
               mkdir -p build
               cd build
               cmake .. -G "Ninja" -DCMAKE_BUILD_TYPE=Release
               ninja
               cd ..
            '''
          }
          post {
            success {
              deploy();
            }
          }
        }
      }
    }
  }
}

def deploy() {
  withAWS(endpointUrl:'https://sfo2.digitaloceanspaces.com', credentials:'jenkins-access') {
    if (env.BRANCH_NAME == 'master') {
      s3Upload(bucket: 'webcore-bin', workingDir:'build', includePathPattern:'*.7z', acl:'PublicRead');
    } else if (env.BRANCH_NAME == 'dev') {
      s3Upload(bucket: 'webcore-bin-dev', workingDir:'build', includePathPattern:'*.7z', acl:'PublicRead');
    }
  }
}