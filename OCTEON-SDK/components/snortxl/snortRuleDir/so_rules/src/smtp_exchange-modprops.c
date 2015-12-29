/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"


/* declare detection functions */
int rule15329eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_server; */
static FlowFlags rule15329flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_SERVER
};

static RuleOption rule15329option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule15329flow0
    }
};
// content:"MODPROPS", nocase; 
static ContentInfo rule15329content1 = 
{
    (u_int8_t *) "MODPROPS", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_NOCASE|CONTENT_BUF_NORMALIZED, /* flags */ // XXX - need to add CONTENT_FAST_PATTERN support
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15329option1 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15329content1
    }
};
// content:"MODPROPS", nocase, relative; 
static ContentInfo rule15329content2 = 
{
    (u_int8_t *) "MODPROPS", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_NOCASE|CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */ // XXX - need to add CONTENT_FAST_PATTERN support
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15329option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15329content2
    }
};

/* references for sid 1 */
/* reference: bugtraq "17908"; */
static RuleReference rule15329ref1 = 
{
    "bugtraq", /* type */
    "17908" /* value */
};

/* reference: cve "2006-0027"; */
static RuleReference rule15329ref2 = 
{
    "cve", /* type */
    "2006-0027" /* value */
};

/* reference: url "www.microsoft.com/technet/security/bulletin/ms06-019.mspx"; */
static RuleReference rule15329ref3 = 
{
    "url", /* type */
    "www.microsoft.com/technet/security/bulletin/ms06-019.mspx" /* value */
};

static RuleReference *rule15329refs[] =
{
    &rule15329ref1,
    &rule15329ref2,
    &rule15329ref3,
    NULL
};
/* metadata for sid 1 */
/* metadata:service smtp, policy balanced-ips alert; */
static RuleMetaData rule15329service1 = 
{
    "service smtp"
};


static RuleMetaData rule15329policy1 = 
{
    "policy balanced-ips drop"
};

static RuleMetaData rule15329policy2 =
{
    "policy security-ips drop"
};

static RuleMetaData *rule15329metadata[] =
{
    &rule15329service1,
    &rule15329policy1,
    &rule15329policy2,
    NULL
};
RuleOption *rule15329options[] =
{
    &rule15329option0,
    &rule15329option1,
    &rule15329option2,
    NULL
};

Rule rule15329 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "any", /* SRCPORT   */
       1, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
       "25", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid (HARDCODED!!!) */
       15329, /* sigid */
       2, /* revision */
   
       "attempted-admin", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "SMTP Microsoft Exchange MODPROPS memory corruption attempt",     /* message */
       rule15329refs /* ptr to references */
       ,rule15329metadata
   },
   rule15329options, /* ptr to rule options */
   &rule15329eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule15329eval(void *p) {
    const u_int8_t *cursor_normal = 0;
    SFSnortPacket *sp = (SFSnortPacket *) p;
    u_int8_t countOne = 0;
    u_int8_t countTwo = 0;
    const u_int8_t *beg_of_payload, *end_of_payload;

    if(sp == NULL)
        return RULE_NOMATCH;

    if(sp->payload == NULL)
        return RULE_NOMATCH;


    // flow:established, to_server;
    if (checkFlow(p, rule15329options[0]->option_u.flowFlags) > 0 ) {
        // content:"MODPROPS"; nocase; 
        if (contentMatch(p, rule15329options[1]->option_u.content, &cursor_normal) > 0) {

            if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &beg_of_payload, &end_of_payload) <= 0)
                return RULE_NOMATCH;

            while ((cursor_normal < end_of_payload) && (*cursor_normal != '\r') && (*cursor_normal != '\n')) {
                if (*cursor_normal == ',') {
                    countOne++;
                }
                cursor_normal++;
            }
            if (contentMatch(p, rule15329options[2]->option_u.content, &cursor_normal) > 0) {
                while ((cursor_normal < end_of_payload) && (*cursor_normal != '\r') && (*cursor_normal != '\n')) {
                    if (*cursor_normal == ',') {
                        countTwo++;
                    }
                    cursor_normal++;
                }
            }
            // Yes, technically these are both off-by-one on the count...but why waste the CPU
            // necessary to increment them both when leaving them as-is yields the same result?
            if (countTwo > countOne) {
                return RULE_MATCH;
            }
        }
    }
    return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule15329,
    NULL
};
*/
 
