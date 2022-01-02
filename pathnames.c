#include"pathnames.h"
#include"ssherr.h"
#include"log.h"
#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<basedir.h>
#include<string.h>

#define PATH_SSH_USER_CONFFILE "config"

#define PATH_SSH_CLIENT_ID_RSA "id_rsa"
#define PATH_SSH_CLIENT_ID_DSA "id_dsa"
#define PATH_SSH_CLIENT_ID_ECDSA "id_ecdsa"
#define PATH_SSH_CLIENT_ID_XMSS "id_xmss"
#define PATH_SSH_CLIENT_ID_ED25519 "id_ed25519"
#define PATH_SSH_CLIENT_ID_ECDSA_SK "id_ecdsa_sk"
#define PATH_SSH_CLIENT_ID_ED25519_SK "id_ed25519_sk"

#define PATH_SSH_USER_HOSTFILE "known_hosts"
#define PATH_SSH_USER_HOSTFILE2 "known_hosts2"

char* path_get_user_client_id_file(enum config_file file) {
        switch (file) {
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_RSA:
                        return PATH_SSH_CLIENT_ID_RSA;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_DSA:
                        return PATH_SSH_CLIENT_ID_DSA;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA:
                        return PATH_SSH_CLIENT_ID_ECDSA;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_XMSS:     
                        return PATH_SSH_CLIENT_ID_XMSS;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519:
                        return PATH_SSH_CLIENT_ID_ED25519;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA_SK:
                        return PATH_SSH_CLIENT_ID_ECDSA_SK;
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519_SK:
                        return PATH_SSH_CLIENT_ID_ED25519_SK;

                case PATH_CONFIG_FILE_SSH_USER_HOSTFILE:
                        return PATH_SSH_USER_HOSTFILE;
                case PATH_CONFIG_FILE_SSH_USER_HOSTFILE2:
                        return PATH_SSH_USER_HOSTFILE2;
                case PATH_CONFIG_FILE_SSH_USER_CONFFILE:
                        return PATH_SSH_USER_CONFFILE;
                default:
                        return NULL;
        }
}

char* path_get_xdg_dir(enum config_file file) {
        switch (file) {
                case PATH_CONFIG_FILE_SSH_USER_CONFFILE:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_RSA:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_DSA:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_XMSS:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA_SK:
                case PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519_SK:
                        return xdgConfigHome(0);
                case PATH_CONFIG_FILE_SSH_USER_HOSTFILE:
                case PATH_CONFIG_FILE_SSH_USER_HOSTFILE2:
                        return xdgDataHome(0);
                default:
                        return NULL;
        }

}

#define PATH_SSH_XDG_CONFIG_DIR "ssh"
char* path_get_user_config_file(enum config_file file) {
        if(file == PATH_CONFIG_FILE_BARE_XDG_CONFIG_HOME) {
                return xdgConfigHome(0);
        }

        char* xdg_dir = path_get_xdg_dir(file);
        char* basename = path_get_user_client_id_file(file);

        if (!xdg_dir || !basename) {
                fatal_f("path_get_user_config_file: invalid file %d", file);
        }

        // Lengths of the individual components plus two forward slashes and a null terminator
        int len = strlen(xdg_dir) + strlen(PATH_SSH_XDG_CONFIG_DIR) + strlen(basename) + 3;
        char* path = malloc(len);

        snprintf(path, len, "%s/%s/%s", xdg_dir, PATH_SSH_XDG_CONFIG_DIR, basename);
        free(xdg_dir);

        return path;
}


