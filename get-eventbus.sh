#!/usr/bin/env bash

if [ ! -d "eventbus" ]; then
    git submodule add https://github.com/mmcshane/eventbus.git
fi

cd eventbus
git pull
cd ..


if [ ! -d "leftright" ]; then
    git submodule add https://github.com/mmcshane/leftright.git
fi

cd leftright
git pull
cd ..
