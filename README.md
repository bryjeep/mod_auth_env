mod_auth_env
============
====================================================================
MOD_AUTH_ENV 0.1 README
====================================================================
Apache ENV Authentication Module

====================================================================
LICENSE
====================================================================
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.

====================================================================
INTRODUCTION 
====================================================================
The purpose of this module is to force a username from environmental
variable into the internals of Apache web server to allow later 
authorization modules to perform queries based on it. 

====================================================================
GETTING STARTED
====================================================================

SOFTWARE DEPENDENCIES
--------------------------------------------------------------------
The module was built and tested on the following libraries/versions:

Apache Portable Runtime - 1.2.8
Apache Portable Runtime Utilities - 1.2.7
Apache Web Server - 2.2.3

Additionally, GNU Make and the auto* tools are necessary for building
mod_auth_env.

Compatibility with other versions will depend on those other libraries.

INSTALLATION INSTRUCTIONS
--------------------------------------------------------------------
Ensure that the follow files are in the working directory:
mod_auth_env.c
mod_auth_env.h

COMPILE INSTRUCTIONS
--------------------------------------------------------------------
Use the APache eXtenSion tool (APXS) to compile and install this 
object as a dynamically shared object (DSO), by either:

apxs -i -lssl -lcurl -c mod_auth_env.c
or
apxs2 -i -lssl -lcurl -c mod_auth_env.c

depending on your Linux distribution.

This release of mod_auth_env includes support for autoconf.  Note that
you must use GNU Make - other Make implementations may work, but are
untested and not recommended.  Use the standard commands below to
compile and install:

./configure; make; make install

configure can take an optional --with-apxs=/path/to/apxs argument to
specify the path to your APXS binary.

CONFIGURING THE SOFTWARE
--------------------------------------------------------------------
First, you must tell Apache to load the module.  In your httpd.conf,
add:

LoadModule auth_env_module /path/to/mod_auth_env.so

Then, in the location(s) you want to protect, use the following
directive:

AuthType ENV

Be sure to set authorization parameters in the locations you
are protecting(e.g. 'require valid-user', 'require group foo')

The following are valid configuration options and their default:

Valid Directory/.htaccess Directives
------------------------------------
Directive: 	AuthEnvUsernameVariable
Default:	AuthUsername
Description:	The environment variable to read as username. 

====================================================================
CONTRIBUTORS 
====================================================================  
Author:
Brian Davidson 	<bdavidson [at] gatech [dot] edu>

Portions of this module are based on code from mod_auth_cas module.

====================================================================
CONTACT INFORMATION AND WEBSITE
====================================================================
We welcome your feedback, suggestions and contributions. Contact us
via email if you have questions, feedback, code submissions, 
and bug reports.

====================================================================