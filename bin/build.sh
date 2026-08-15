#!/bin/bash

KEEB_PATH=$HOME/.keeb
QMK_PATH=$HOME/.qmk
KB=keyboardio/atreus
KM=hazenreid
KEYMAP_PATH=$QMK_PATH/keyboards/$KB/keymaps/$KM

pushd $QMK_PATH
git pull
command cp -a $KEEB_PATH/keymap $KEYMAP_PATH
SKIP_FLASHING_SUPPORT=1 util/docker_build.sh $KB:$KM
command rm -rf $KEYMAP_PATH
command mv *.hex ~/Downloads
popd
