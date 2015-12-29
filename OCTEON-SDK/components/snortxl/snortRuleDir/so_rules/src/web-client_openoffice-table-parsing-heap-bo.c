/*
  XXX does not use built-in detection function! XXX

alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT OpenOffice Word document table parsing multiple heap based buffer overflow attempt"; flowbits:isset,http.doc; flow:to_client,established; content:"|00 00 00 FF 00 00 00 FF 00 00 00 FF 00 00 00 FF 22 56|"; metadata:policy security-ips drop, service http; reference:cve,2009-0200; reference:cve,2009-0201; reference:bugtraq,36200; classtype:attempted-user; sid:17665; rev:1;)
*/
/*
 * Vuln Title: OpenOffice Word document table parsing multiple heap based buffer overflow
 *
 * Copyright (C) 2005-2010 Sourcefire, Inc. All Rights Reserved
 *
 * Written by Sojeong Hong, Sourcefire VRT <shong@sourcefire.com>
 *
 * Auto-generated by shong
 *
 * This file may contain proprietary rules that were created, tested and
 * certified by Sourcefire, Inc. (the "VRT Certified Rules") as well as
 * rules that were created by Sourcefire and other third parties and
 * distributed under the GNU General Public License (the "GPL Rules").  The
 * VRT Certified Rules contained in this file are the property of
 * Sourcefire, Inc. Copyright 2005 Sourcefire, Inc. All Rights Reserved.
 * The GPL Rules created by Sourcefire, Inc. are the property of
 * Sourcefire, Inc. Copyright 2002-2005 Sourcefire, Inc. All Rights
 * Reserved.  All other GPL Rules are owned and copyrighted by their
 * respective owners (please see www.snort.org/contributors for a list of
 * owners and their respective copyrights).  In order to determine what
 * rules are VRT Certified Rules or GPL Rules, please refer to the VRT
 * Certified Rules License Agreement.
 */

#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

//#define DEBUG 1
#ifdef DEBUG
#define DEBUG_SO(code) code
#else
#define DEBUG_SO(code)
#endif

/* declare detection functions */
int rule17665eval(void *p);

/* declare rule data structures */
/* flowbits:isset "http.doc"; */
static FlowBitsInfo rule17665flowbits0 =
{
    "http.doc",
    FLOWBIT_ISSET,
    0,
};

static RuleOption rule17665option0 =
{
    OPTION_TYPE_FLOWBIT,
    {
        &rule17665flowbits0
    }
};
/* flow:established, to_client; */
static FlowFlags rule17665flow1 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule17665option1 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule17665flow1
    }
};
// content:"|00 00 00 FF 00 00 00 FF 00 00 00 FF 00 00 00 FF 22|V", depth 0, fast_pattern; 
static ContentInfo rule17665content2 = 
{
    (u_int8_t *) "|00 00 00 FF 00 00 00 FF 00 00 00 FF 00 00 00 FF 22|V", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule17665option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule17665content2
    }
};

/* references for sid 17665 */
/* reference: bugtraq "36200"; */
static RuleReference rule17665ref1 = 
{
    "bugtraq", /* type */
    "36200" /* value */
};

/* reference: cve "2009-0200"; */
static RuleReference rule17665ref2 = 
{
    "cve", /* type */
    "2009-0200" /* value */
};

/* reference: cve "2009-0201"; */
static RuleReference rule17665ref3 = 
{
    "cve", /* type */
    "2009-0201" /* value */
};

static RuleReference *rule17665refs[] =
{
    &rule17665ref1,
    &rule17665ref2,
    &rule17665ref3,
    NULL
};
/* metadata for sid 17665 */
/* metadata:service http, policy security-ips drop; */
static RuleMetaData rule17665service1 = 
{
    "service http"
};


static RuleMetaData rule17665policy1 = 
{
    "policy security-ips drop"
};

static RuleMetaData rule17665policy2 =
{
    "policy balanced-ips drop"
};


static RuleMetaData *rule17665metadata[] =
{
    &rule17665service1,
    &rule17665policy1,
    &rule17665policy2,
    NULL
};

RuleOption *rule17665options[] =
{
    &rule17665option0,
    &rule17665option1,
    &rule17665option2,
    NULL
};

Rule rule17665 = {
   /* rule header, akin to => tcp any any -> any any */
   {
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       17665, /* sigid */
       2, /* revision */
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "WEB-CLIENT OpenOffice Word document table parsing multiple heap based buffer overflow attempt",     /* message */
       rule17665refs /* ptr to references */
       ,rule17665metadata
   },
   rule17665options, /* ptr to rule options */
   &rule17665eval, /* DO NOT use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule17665eval(void *p) {
    const u_int8_t *cursor_normal = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;

    const u_int8_t *end_of_payload;
    u_int8_t itcFirst;    // index of first cell to delete
    u_int8_t itcLim;      // index of last cell to delete

    DEBUG_SO(const char *name="rule17665eval";)
    DEBUG_SO(printf("%s: enter\n", name);)        

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;
    
    // flowbits:isset "http.doc";
    if (processFlowbits(p, rule17665options[0]->option_u.flowBit) > 0) {
        // flow:established, to_client;
        if (checkFlow(p, rule17665options[1]->option_u.flowFlags) > 0 ) {

            if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_payload) <= 0)
                return RULE_NOMATCH;
            
            // sprmTDelete opcode = 0x5622 in little endian format
            // content:"|00 00 00 FF 00 00 00 FF 00 00 00 FF 00 00 00 FF 22|V", depth 0, fast_pattern;
            while (contentMatch(p, rule17665options[2]->option_u.content, &cursor_normal) > 0) {

                DEBUG_SO(printf("%s: \"|00 00 00 FF 00 00 00 FF 00 00 00 FF 00 00 00 FF 22 56|\" found \n", name);)

                if (cursor_normal + 2 > end_of_payload)
                    return RULE_NOMATCH;
                
                itcFirst = *cursor_normal;
                itcLim   = *(cursor_normal + 1);

                DEBUG_SO(printf("%s: itcFirst = 0x%02x, itcLim = 0x%02x\n", name, itcFirst, itcLim);)

                if ((itcLim > 64) || (itcFirst > itcLim))
                    return RULE_MATCH;                
            }
        }
    }
    return RULE_NOMATCH;
}
/*
Rule *rules[] = {
    &rule17665,
    NULL
};
*/
