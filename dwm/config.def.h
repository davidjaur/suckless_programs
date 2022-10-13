/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static unsigned int snap      = 32;       /* snap pixel */
static int showbar            = 1;        /* 0 means no bar */
static int topbar             = 1;        /* 0 means bottom bar */
static char font[]            = "Iosevka Nerd Font:size=10";
static char dmenufont[]       = "Iosevka Nerd Font:size=10";
static const char *fonts[]          = { font };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char dmenu_selected_bg[]      = "#005577";
static char dmenu_selected_fg[]      = "#005577";
static char dmenu_unselected_bg[]    = "#005577";
static char dmenu_unselected_fg[]    = "#005577";
static char statusbar_bg[]     = "#005577";
static char statusbar_fg[]     = "#005577";
static char tagbar_selected_bg[]    = "#005577";
static char tagbar_selected_fg[]    = "#005577";
static char tagbar_unselected_bg[]  = "#005577";
static char tagbar_unselected_fg[]  = "#005577";
static char infobar_selected_bg[]   = "#005577";
static char infobar_selected_fg[]   = "#005577";
static char infobar_unselected_bg[]   = "#005577";
static char infobar_unselected_fg[]   = "#005577";
static char *colors[][3] = {
	       /*               fg           bg           border   */
	       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	       [SchemeStatus]  = { statusbar_fg, statusbar_bg,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
     	       [SchemeTagsSel]  = { tagbar_selected_fg, tagbar_selected_bg,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	       [SchemeTagsNorm]  = { tagbar_unselected_fg, tagbar_unselected_bg,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	       [SchemeInfoSel]  = { infobar_selected_fg, infobar_selected_bg,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	       [SchemeInfoNorm]  = { infobar_unselected_fg, infobar_unselected_bg,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "", "異", "", "", "", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static int nmaster     = 1;    /* number of clients in master area */
static int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", dmenu_unselected_bg, "-nf", dmenu_unselected_fg, "-sb", dmenu_selected_bg, "-sf", dmenu_selected_fg, NULL };
static const char *termcmd[]  = { "alacritty", NULL };


/*
* Xresources preferences to load at startup
*/
ResourcePref resources[] = {
			{ "font",               STRING,  &font },
			{ "dmenufont",          STRING,  &dmenufont },
			{ "normbgcolor",        STRING,  &normbgcolor },
			{ "normbordercolor",    STRING,  &normbordercolor },
			{ "normfgcolor",        STRING,  &normfgcolor },
			{ "selbgcolor",         STRING,  &selbgcolor },
			{ "selbordercolor",     STRING,  &selbordercolor },
			{ "selfgcolor",         STRING,  &selfgcolor },
			{ "dmenu_selected_bg",  STRING,  &dmenu_selected_bg },
			{ "dmenu_selected_fg",  STRING,  &dmenu_selected_fg },
			{ "dmenu_unselected_bg",  STRING,  &dmenu_unselected_bg },
			{ "dmenu_unselected_fg",  STRING,  &dmenu_unselected_fg },
			{ "statusbar_bg",       STRING,  &statusbar_bg },
			{ "statusbar_fg",       STRING,  &statusbar_fg },
			{ "tagbar_selected_bg", STRING,  &tagbar_selected_bg },
			{ "tagbar_selected_fg", STRING,  &tagbar_selected_fg },
			{ "tagbar_unselected_bg", STRING,  &tagbar_unselected_bg },
			{ "tagbar_unselected_fg", STRING,  &tagbar_unselected_fg },
			{ "infobar_selected_bg", STRING,  &infobar_selected_bg },
			{ "infobar_selected_fg", STRING,  &infobar_selected_fg },
			{ "infobar_unselected_bg", STRING,  &infobar_unselected_bg },
			{ "infobar_unselected_fg", STRING,  &infobar_unselected_fg },
			{ "borderpx",          	INTEGER, &borderpx },
			{ "snap",          		INTEGER, &snap },
			{ "showbar",          	INTEGER, &showbar },
			{ "topbar",          	INTEGER, &topbar },
			{ "nmaster",          	INTEGER, &nmaster },
			{ "resizehints",       	INTEGER, &resizehints },
			{ "mfact",      	 	FLOAT,   &mfact },
};

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	{ MODKEY,                       XK_n,      shiftview,      {.i = +1  } },
	{ MODKEY,                       XK_b,      shiftview,      {.i = -1  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
