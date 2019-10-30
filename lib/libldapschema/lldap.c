
/*
 *  LDAP Utilities
 *  Copyright (C) 2012, 2019 David M. Syzdek <david@syzdek.net>.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *     1. Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 *  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 *  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 *  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 *  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 *   @file src/ldapschema/lerror.c  contains error functions and variables
 */
#define _LIB_LIBLDAPSCHEMA_LLDAP_C 1
#include "lldap.h"

///////////////
//           //
//  Headers  //
//           //
///////////////
#pragma mark - Headers

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>


/////////////////
//             //
//  Functions  //
//             //
/////////////////
#pragma mark - Functions

int ldapschema_fetch(LDAPSchema * lsd, LDAP * ld)
{
   int                  err;
   int                  x;
   struct timeval       timeout;
   LDAPMessage        * res;
   LDAPMessage        * msg;
   char              ** dns;
   char              ** attrs;
   struct berval     ** vals;
   void               * ptr;

   assert(lsd != NULL);
   assert(ld  != NULL);

   timeout.tv_sec    = 5;
   timeout.tv_usec   = 0;

   attrs = NULL;
   if ((err = ldapschema_definition_split(lsd, "( + * )", 7, &attrs)) == -1)
      return(lsd->errcode);

   // searches for schema DN
   res = NULL;
   if ((err = ldap_search_ext_s(ld, "", LDAP_SCOPE_BASE, "(objectclass=*)", attrs, 0, NULL, NULL, NULL, 0, &res)) != LDAP_SUCCESS)
   {
      ldapschema_value_free(attrs);
      return(err);
   };
   if ((msg = ldap_first_entry(ld, res)) == NULL)
   {
      ldap_msgfree(res);
      return(-1);
   };
   if ((dns = ldap_get_values(ld, msg, "subschemaSubentry")) == NULL)
   {
      ldap_msgfree(res);
      ldap_value_free(dns);
      return(-1);
   };
   ldap_msgfree(res);

   // searches for schema entry
   res = NULL;
   if ((err = ldap_search_ext_s(ld, dns[0], LDAP_SCOPE_BASE, "(objectclass=*)", attrs, 0, NULL, NULL, NULL, 0, &res)) != LDAP_SUCCESS)
   {
      ldap_value_free(dns);
      ldapschema_value_free(attrs);
      return(-1);
   };
   ldap_value_free(dns);
   ldapschema_value_free(attrs);
   dns   = NULL;
   attrs = NULL;
   if ((msg = ldap_first_entry(ld, res)) == NULL)
   {
      ldap_msgfree(res);
      return(-1);
   };

   // process ldapSyntaxes
   if ((vals = ldap_get_values_len(ld, msg, "ldapSyntaxes")) != NULL)
   {
      for(x = 0; ((vals[x])); x++)
      {
         if ((ptr = ldapschema_parse_syntax(lsd, vals[x])) == NULL)
         {
            ldap_value_free_len(vals);
            ldap_msgfree(res);
            return(-1);
         };
      };
      ldap_value_free_len(vals);
   };

   // process attributeTypes
   if ((vals = ldap_get_values_len(ld, msg, "attributeTypes")) != NULL)
   {
      for(x = 0; ((vals[x])); x++)
      {
         if ((ptr = ldapschema_parse_attributetype(lsd, vals[x])) == NULL)
         {
            ldap_value_free_len(vals);
            ldap_msgfree(res);
            return(-1);
         };
      };
      ldap_value_free_len(vals);
   };

   ldap_msgfree(res);

   return(LDAP_SUCCESS);
}

/* end of source file */