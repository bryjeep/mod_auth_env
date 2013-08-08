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

#include "apr_strings.h"

#include "apr_strings.h"
#define APR_WANT_STRFUNC        /* for strcasecmp */
#include "apr_want.h"

#include "ap_config.h"
#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_protocol.h"
#include "http_request.h"
#include "ap_provider.h"

#include "mod_auth_env.h"

static void *create_auth_env_dir_config(apr_pool_t *p, char *d)
{
    auth_env_config_rec *conf = apr_pcalloc(p, sizeof(*conf));

    conf->dir = d;
    conf->env_variable = ENV_DEFAULT_USERNAME_VARIABLE;
    return conf;
}

int error_out_table_func(void *req, const char *key, const char *value) {
    request_rec *r = (request_rec *)req;
    if (key == NULL || value == NULL || value[0] == '\0')
        return 1;
    
	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
	                "%s => %s\n", key, value);
    return 1;
}

/* 
 * Determine user ID from environment variable
 */
static int authenticate_env_user(request_rec *r)
{
    auth_env_config_rec *conf = ap_get_module_config(r->per_dir_config,
                                                       &auth_env_module);
                                                       
	extern char **environ;
    const char *env_user = apr_table_get(r->subprocess_env,conf->env_variable);
    
    /* set the user */
    r->user = env_user;
    
    if(!env_user){
    	ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "env variable %s not found", conf->env_variable);

    	apr_table_do(error_out_table_func, r, r->subprocess_env,NULL);
    	
    	return HTTP_UNAUTHORIZED;
    }
    return OK;
}

static void env_register_hooks(apr_pool_t *p)
{
    ap_hook_check_user_id(authenticate_env_user,NULL,NULL,APR_HOOK_MIDDLE);
}

static const command_rec auth_env_cmds[] =
{
	AP_INIT_TAKE1("AuthEnvUsernameVariable", ap_set_string_slot, (void *) APR_OFFSETOF(auth_env_config_rec,env_variable), OR_AUTHCFG, "Define the name of the environment variable containing the username"),
    {NULL}
};


module AP_MODULE_DECLARE_DATA auth_env_module =
{
    STANDARD20_MODULE_STUFF,
    create_auth_env_dir_config,  /* dir config creater */
    NULL,                          /* dir merger --- default is to override */
    NULL,                          /* server config */
    NULL,                          /* merge server config */
    auth_env_cmds,               /* command apr_table_t */
    env_register_hooks                 /* register hooks */
};