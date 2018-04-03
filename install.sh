#!/bin/bash

MAIN_SOURCE_DIR=$(dirname $(realpath $0))

MODULE_SOURCE_DIR=${MAIN_SOURCE_DIR}/kernel_module
MODULE_FILE=${MODULE_SOURCE_DIR}/kiki.ko.gz
MODULE_HEADER_FILE=${MODULE_SOURCE_DIR}/src/kiki.h
MODULE_CONFIG_FILE=${MODULE_SOURCE_DIR}/conf/kiki.conf

C_API_SOURCE_DIR=${MAIN_SOURCE_DIR}/c_api

MODULES_CONFIG_DIR=/etc/modules-load.d
MODULES_DIR=/lib/modules/$(uname -r)
MODULE_INSTALL_DIR=${MODULES_DIR}/kernel/drivers

INCLUDE_DIR=/usr/include

MAN_SOURCE_DIR=${MAIN_SOURCE_DIR}/man
MAN_INSTALL_DIR=/usr/share/man


# exit and die function in case of problem

function error_and_exit {
    echo $1
    exit $2
}

# Check for dependencies

[ -r /usr/include/linux/kernel.h ] && echo "dependencies: MET" || error_and_exit "KERNEL HEADERS DO NOT SEEM TO BE INSTALLED: please install it using \"sudo apt-get install build-essential linux-headers-$(uname -r)\"" 6


# Compile Kernel Module (The Driver)

echo cleaning kernel_module source directory
make -C ${MODULE_SOURCE_DIR} clean
echo compile module
make -C ${MODULE_SOURCE_DIR} -j

[ -r ${MODULE_SOURCE_DIR}/kiki.ko ] && echo "module compilation: SUCCESS" || error_and_exit "KERNEL MODULE COMPILATION FAILED!!!" 1


# Install Kernel Module (The Driver) & its Header & its loading configuration file

echo installing module
sudo make -C ${MODULE_SOURCE_DIR} install

[ -r ${MODULE_INSTALL_DIR}/kiki.ko ] && echo "module installation: SUCCESS" || error_and_exit "KERNEL MODULE INSTALLATION FAILED!!!" 2
[ -r ${INCLUDE_DIR}/kiki.h ] && echo "module header installation: SUCCESS" || error_and_exit "KERNEL MODULE HEADER INSTALLATION FAILED!!!" 3


# Install Main Competition Header

echo installing C api header
sudo install -m 644 ${C_API_SOURCE_DIR}/include/kiki_api.h ${INCLUDE_DIR}

[ -r ${INCLUDE_DIR}/kiki_api.h ] && echo "C API header installation: SUCCESS" || error_and_exit "C API HEADER INSTALLATION FAILED!!!" 4


# Install The Required Documentation

echo installing kernel module man page
sudo install -m 644 ${MAN_SOURCE_DIR}/man4/kiki.4 ${MAN_INSTALL_DIR}/man4/kiki.4
sudo install -m 644 ${MAN_SOURCE_DIR}/man4/kiki-fr.4 ${MAN_INSTALL_DIR}/man4/kiki-fr.4

[ -r ${MAN_INSTALL_DIR}/man4/kiki.4 ] && echo "kernel interface doc installation: SUCCESS" || error_and_exit "DOCUMENTATION INSTALLATION FAILED!!!" 5


echo installing api man pages
for file in ${MAN_SOURCE_DIR}/man3/*.3; do
    sudo install -m 644 $file ${MAN_INSTALL_DIR}/man3/$(basename $file)

    [ -r ${MAN_INSTALL_DIR}/man3/$(basename $file) ] && echo "api doc file installation: SUCCESS" || error_and_exit "DOCUMENTATION INSTALLATION FAILED!!!" 5
done



# Remove all source code

echo NOW, PLEASE DELETE ALL SOURCE CODE FILES GIVEN, CONTESTANTS MAY NOT ACCESS IT.
echo AFTER THAT, PLEASE REBOOT THE MACHINE AND MAKE SURE SYSTEM IS RUNNING FINE.
echo ---
echo MAINTENANT, SVP DETRUIRE TOUT FICHIER SOURCE FOURNI, LES PARTICIPANTS NE DOIVENT PAS Y AVOIR ACCES.
echo ENSUITE, SVP REDEMARRER LA MACHINE ET VERIFIER QUE LE SYSTEME ROULE NORMALEMENT.
