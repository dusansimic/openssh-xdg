/* $OpenBSD: pathnames.h,v 1.31 2019/11/12 19:33:08 markus Exp $ */

/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 */

#define ETCDIR				"/etc"

#ifndef SSHDIR
#define SSHDIR				ETCDIR "/ssh"
#endif

#ifndef _PATH_SSH_PIDDIR
#define _PATH_SSH_PIDDIR		"/var/run"
#endif

/*
 * System-wide file containing host keys of known hosts.  This file should be
 * world-readable.
 */
#define _PATH_SSH_SYSTEM_HOSTFILE	SSHDIR "/ssh_known_hosts"
/* backward compat for protocol 2 */
#define _PATH_SSH_SYSTEM_HOSTFILE2	SSHDIR "/ssh_known_hosts2"

/*
 * Of these, ssh_host_key must be readable only by root, whereas ssh_config
 * should be world-readable.
 */
#define _PATH_SERVER_CONFIG_FILE	SSHDIR "/sshd_config"
#define _PATH_HOST_CONFIG_FILE		SSHDIR "/ssh_config"
#define _PATH_HOST_DSA_KEY_FILE		SSHDIR "/ssh_host_dsa_key"
#define _PATH_HOST_ECDSA_KEY_FILE	SSHDIR "/ssh_host_ecdsa_key"
#define _PATH_HOST_ED25519_KEY_FILE	SSHDIR "/ssh_host_ed25519_key"
#define _PATH_HOST_XMSS_KEY_FILE	SSHDIR "/ssh_host_xmss_key"
#define _PATH_HOST_RSA_KEY_FILE		SSHDIR "/ssh_host_rsa_key"
#define _PATH_DH_MODULI			SSHDIR "/moduli"

#ifndef _PATH_SSH_PROGRAM
#define _PATH_SSH_PROGRAM		"/usr/bin/ssh"
#endif

/*
 * The process id of the daemon listening for connections is saved here to
 * make it easier to kill the correct daemon when necessary.
 */
#define _PATH_SSH_DAEMON_PID_FILE	_PATH_SSH_PIDDIR "/sshd.pid"

enum config_file {
        PATH_CONFIG_FILE_SSH_USER_HOSTFILE,
        PATH_CONFIG_FILE_SSH_USER_HOSTFILE2,

        PATH_CONFIG_FILE_SSH_CLIENT_ID_DSA,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_ECDSA_SK,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_RSA,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_XMSS,
        PATH_CONFIG_FILE_SSH_CLIENT_ID_ED25519_SK,

        PATH_CONFIG_FILE_SSH_USER_PERMITTED_KEYS,
        PATH_CONFIG_FILE_SSH_USER_PERMITTED_KEYS2,

        PATH_CONFIG_FILE_SSH_USER_CONFFILE,
        PATH_CONFIG_FILE_SSH_USER_RC,
        PATH_CONFIG_FILE_SSH_USER_CONFIG_DIR,
        PATH_CONFIG_FILE_SSH_USER_CACHE_DIR,
        PATH_CONFIG_FILE_BARE_XDG_CONFIG_HOME,
        PATH_CONFIG_FILE_BARE_XDG_CACHE_HOME
};


char* path_get_user_config_file(enum config_file file);

#define _PATH_SSH_SYSTEM_RC		SSHDIR "/sshrc"

/*
 * Ssh-only version of /etc/hosts.equiv.  Additionally, the daemon may use
 * ~/.rhosts and /etc/hosts.equiv if rhosts authentication is enabled.
 */
#define _PATH_SSH_HOSTS_EQUIV		SSHDIR "/shosts.equiv"
#define _PATH_RHOSTS_EQUIV		"/etc/hosts.equiv"

/*
 * Default location of askpass
 */
#ifndef _PATH_SSH_ASKPASS_DEFAULT
#define _PATH_SSH_ASKPASS_DEFAULT	"/usr/X11R6/bin/ssh-askpass"
#endif

/* Location of ssh-keysign for hostbased authentication */
#ifndef _PATH_SSH_KEY_SIGN
#define _PATH_SSH_KEY_SIGN		"/usr/libexec/ssh-keysign"
#endif

/* Location of ssh-pkcs11-helper to support keys in tokens */
#ifndef _PATH_SSH_PKCS11_HELPER
#define _PATH_SSH_PKCS11_HELPER		"/usr/libexec/ssh-pkcs11-helper"
#endif

/* Location of ssh-sk-helper to support keys in security keys */
#ifndef _PATH_SSH_SK_HELPER
#define _PATH_SSH_SK_HELPER		"/usr/libexec/ssh-sk-helper"
#endif

/* xauth for X11 forwarding */
#ifndef _PATH_XAUTH
#define _PATH_XAUTH			"/usr/X11R6/bin/xauth"
#endif

/* UNIX domain socket for X11 server; displaynum will replace %u */
#ifndef _PATH_UNIX_X
#define _PATH_UNIX_X "/tmp/.X11-unix/X%u"
#endif

/* for scp */
#ifndef _PATH_CP
#define _PATH_CP			"cp"
#endif

/* for sftp */
#ifndef _PATH_SFTP_SERVER
#define _PATH_SFTP_SERVER		"/usr/libexec/sftp-server"
#endif

/* chroot directory for unprivileged user when UsePrivilegeSeparation=yes */
#ifndef _PATH_PRIVSEP_CHROOT_DIR
#define _PATH_PRIVSEP_CHROOT_DIR	"/var/empty"
#endif

/* for passwd change */
#ifndef _PATH_PASSWD_PROG
#define _PATH_PASSWD_PROG             "/usr/bin/passwd"
#endif

#ifndef _PATH_LS
#define _PATH_LS			"ls"
#endif

/* Askpass program define */
#ifndef ASKPASS_PROGRAM
#define ASKPASS_PROGRAM         "/usr/lib/ssh/ssh-askpass"
#endif /* ASKPASS_PROGRAM */
