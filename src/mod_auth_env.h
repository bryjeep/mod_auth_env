/*
 *
 * Copyright 2010 Phillip Ames / Matt Smith
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 * mod_auth_env.h
 * Apache ENV Authentication Module
 * Version 0.1
 *
 * Author:
 * Brian Davidson       <bdavidson [at] gatech [dot] edu>
 */

#ifndef MOD_AUTH_ENV_H
#define MOD_AUTH_ENV_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stddef.h>
#include "ap_release.h"

#ifndef AP_SERVER_MAJORVERSION_NUMBER
	#ifndef AP_SERVER_MINORVERSION_NUMBER
		#define APACHE2_0
	#endif
#endif

#ifndef APACHE2_0
	#ifdef AP_SERVER_MAJORVERSION_NUMBER
		#ifdef AP_SERVER_MINORVERSION_NUMBER
			#if ((AP_SERVER_MAJORVERSION_NUMBER == 2) && (AP_SERVER_MINORVERSION_NUMBER == 0))
				#define APACHE2_0
			#endif
		#endif
	#endif
#endif

#define ENV_DEFAULT_USERNAME_VARIABLE "AuthUsername"

typedef struct {
    char *dir;
    char *env_variable;
} auth_env_config_rec;

module AP_MODULE_DECLARE_DATA auth_env_module;

#endif /* MOD_AUTH_ENV_H */
