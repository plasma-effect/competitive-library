set -euo pipefail
VERSION=1.15.2

if [ ! -e "googletest-${VERSION}.tar.gz" ]; then
  curl -LJO "https://github.com/google/googletest/releases/download/v${VERSION}/googletest-${VERSION}.tar.gz"
fi

if [ ! -e "googletest" ]; then
  tar xf "googletest-${VERSION}.tar.gz"
  mv "googletest-${VERSION}" googletest
fi

if [ ! -e "googletest/build/lib" ]; then
  cd googletest
  mkdir -p build
  cd build
  cmake ..
  make
fi
