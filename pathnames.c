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

char* path_get_user_config_file(enum config_file file) {
        char* xdg_config_home = 0;
        char* xdg_data_home = 0;
        char* path = 0;
        int len = 0;

        switch (file) {
                case PATH_NAME_CONFIG_FILE_SSH_USER_CONFFILE:
                        xdg_config_home = xdgConfigHome(0);
                        len = strlen(xdg_config_home) + strlen(PATH_SSH_USER_CONFFILE) + 6;
                        path = malloc(len);
                        snprintf(path, len, "%s/ssh/%s", xdg_config_home, PATH_SSH_USER_CONFFILE);
                        free(xdg_config_home);
                        return path;
                case PATH_NAME_CONFIG_FILE_SSH_CLIENT_ID_RSA:
                        xdg_config_home = xdgConfigHome(0);
                        len = strlen(xdg_config_home) + strlen(PATH_SSH_CLIENT_ID_RSA) + 6;
                        path = malloc(len);
                        snprintf(path, len, "%s/ssh/%s", xdg_config_home, PATH_SSH_CLIENT_ID_RSA);
                        free(xdg_config_home);
                        return path;
                case PATH_NAME_CONFIG_FILE_SSH_USER_DIR:
                        xdg_config_home = xdgConfigHome(0);
                        len = strlen(xdg_config_home) + 6;
                        path = malloc(len);
                        snprintf(path, len, "%s/ssh", xdg_config_home);
                        free(xdg_config_home);
                        return path;
                case PATH_NAME_CONFIG_FILE_BARE_XDG_CONFIG_HOME:
                        return xdgConfigHome(0);
                default:
                        return xdgConfigHome(0);
        }
}


