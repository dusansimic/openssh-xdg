#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<basedir.h>
#include<string.h>

#include"pathnames.h"
#include"ssherr.h"
#include"xmalloc.h"
#include"log.h"
#include"config.h"

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

#define PATH_SSH_USER_PERMITTED_KEYS "authorized_keys"
#define PATH_SSH_USER_PERMITTED_KEYS2 "authorized_keys2"

#define PATH_SSH_USER_RC "rc"

#define PATH_SSH_XDG_CONFIG_DIR "ssh"

char* path_get_user_client_id_file(enum config_file file) {
        switch (file) {
                case CONFIG_FILE_SSH_CLIENT_ID_RSA:
                        return PATH_SSH_CLIENT_ID_RSA;
                case CONFIG_FILE_SSH_CLIENT_ID_DSA:
                        return PATH_SSH_CLIENT_ID_DSA;
                case CONFIG_FILE_SSH_CLIENT_ID_ECDSA:
                        return PATH_SSH_CLIENT_ID_ECDSA;
                case CONFIG_FILE_SSH_CLIENT_ID_XMSS:
                        return PATH_SSH_CLIENT_ID_XMSS;
                case CONFIG_FILE_SSH_CLIENT_ID_ED25519:
                        return PATH_SSH_CLIENT_ID_ED25519;
                case CONFIG_FILE_SSH_CLIENT_ID_ECDSA_SK:
                        return PATH_SSH_CLIENT_ID_ECDSA_SK;
                case CONFIG_FILE_SSH_CLIENT_ID_ED25519_SK:
                        return PATH_SSH_CLIENT_ID_ED25519_SK;

                case CONFIG_FILE_SSH_USER_HOSTFILE:
                        return PATH_SSH_USER_HOSTFILE;
                case CONFIG_FILE_SSH_USER_HOSTFILE2:
                        return PATH_SSH_USER_HOSTFILE2;
                case CONFIG_FILE_SSH_USER_CONFFILE:
                        return PATH_SSH_USER_CONFFILE;

                case CONFIG_FILE_SSH_USER_PERMITTED_KEYS:
                        return PATH_SSH_USER_PERMITTED_KEYS;
                case CONFIG_FILE_SSH_USER_PERMITTED_KEYS2:
                        return PATH_SSH_USER_PERMITTED_KEYS2;

                case CONFIG_FILE_SSH_USER_RC:
                        return PATH_SSH_USER_RC;
                default:
                        return NULL;
        }
}

const char* path_get_xdg_dir(enum config_file file) {
        switch (file) {
                case CONFIG_FILE_SSH_USER_CONFFILE:
                case CONFIG_FILE_SSH_CLIENT_ID_RSA:
                case CONFIG_FILE_SSH_CLIENT_ID_DSA:
                case CONFIG_FILE_SSH_CLIENT_ID_ECDSA:
                case CONFIG_FILE_SSH_CLIENT_ID_XMSS:
                case CONFIG_FILE_SSH_CLIENT_ID_ED25519:
                case CONFIG_FILE_SSH_CLIENT_ID_ECDSA_SK:
                case CONFIG_FILE_SSH_CLIENT_ID_ED25519_SK:

                case CONFIG_FILE_SSH_USER_PERMITTED_KEYS:
                case CONFIG_FILE_SSH_USER_PERMITTED_KEYS2:

                case CONFIG_FILE_SSH_USER_RC:
                        return xdgConfigHome(0);
                case CONFIG_FILE_SSH_USER_HOSTFILE:
                case CONFIG_FILE_SSH_USER_HOSTFILE2:
                        return xdgCacheHome(0);
                default:
                        return NULL;
        }

}

char* path_get_user_config_file(enum config_file file) {
        // XDG functions return a const char* but since we aren't passing it a buffer we can cast it to a char*
        // since it just allocates when it is called.
        if(file == CONFIG_FILE_BARE_XDG_CONFIG_HOME) {
                return (char*) xdgConfigHome(0);
        } else if(file == CONFIG_FILE_BARE_XDG_CACHE_HOME) {
                return (char*) xdgCacheHome(0);
        } else if(file == CONFIG_FILE_SSH_USER_CACHE_DIR || file == CONFIG_FILE_SSH_USER_CONFIG_DIR) {

                char* xdg_dir = (char*)((file == CONFIG_FILE_SSH_USER_CACHE_DIR) ? xdgCacheHome(0) : xdgConfigHome(0));

                int len = strlen(xdg_dir) + strlen(PATH_SSH_XDG_CONFIG_DIR) + 2;
                char* temp_path = xcalloc(len, sizeof(char));

                snprintf(temp_path, len, "%s/%s", xdg_dir, PATH_SSH_XDG_CONFIG_DIR);

                free(xdg_dir);
                return temp_path;
        }

        char* xdg_dir = (char *) path_get_xdg_dir(file);
        char* basename = path_get_user_client_id_file(file);

        if (!xdg_dir || !basename) {
                fatal_f("invalid file %d", file);
        }

        // Lengths of the individual components plus two forward slashes and a null terminator
        int len = strlen(xdg_dir) + strlen(PATH_SSH_XDG_CONFIG_DIR) + strlen(basename) + 3;
        char* path = malloc(len);

        snprintf(path, len, "%s/%s/%s", xdg_dir, PATH_SSH_XDG_CONFIG_DIR, basename);
        free(xdg_dir);

        return path;
}


