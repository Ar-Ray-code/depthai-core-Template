SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $SCRIPT_DIR

# reset depthai-core
rm -rf depthai-core
git submodule update --init

# depthai install-dependencies
sudo curl -fL https://docs.luxonis.com/install_dependencies.sh | bash


# depthai build ------------
cd ${SCRIPT_DIR}/depthai-core/
git submodule update --init --recursive
cmake -S. -Bbuild
cmake --build build --target install -j$(nproc)

# remove depthai-src (optional)
ls $(pwd) | grep -v -E 'build' | xargs rm -rf
cd ${SCRIPT_DIR}

# build target -----
# mkdir -p ${SCRIPT_DIR}/build
# cd ${SCRIPT_DIR}/build/
# cmake ..
# make -j$(nproc)

echo "Done!"
unset SCRIPT_DIR