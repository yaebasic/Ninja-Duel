# ----------------------------
# Makefile Options
# ----------------------------

NAME = NinjDuel
DESCRIPTION = "Ninja Duel"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
