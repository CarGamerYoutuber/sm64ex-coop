// 0x05006088
static const s16 blargg_seg5_animvalue_05006088[] = {
    0x0000, 0x0016, 0x0018, 0x001C, 0x0022, 0x002A, 0x0033, 0x003D,
    0x0047, 0x0052, 0x005C, 0x0065, 0x006D, 0x0073, 0x0077, 0x0078,
    0x0077, 0x0074, 0x0070, 0x006B, 0x0064, 0x005C, 0x0054, 0x004C,
    0x0043, 0x003A, 0x0031, 0x0029, 0x0022, 0x001C, 0x0016, 0x3FFF,
    0x8785, 0x804C, 0x0BCD, 0x0BF1, 0x0C51, 0x0CD8, 0x0D72, 0x0E0C,
    0x0E91, 0x0EEE, 0x0F0F, 0x0EFC, 0x0ED0, 0x0E8F, 0x0E3C, 0x0DDE,
    0x0D78, 0x0D10, 0x0CA9, 0x0C48, 0x0BF2, 0x0BAB, 0x0B77, 0x0B5A,
    0x0B50, 0x0B55, 0x0B64, 0x0B7B, 0x0B94, 0x0BAD, 0x0BC1, 0x0BCD,
    0x76C1, 0x0000,
};

// 0x0500610C
static const u16 blargg_seg5_animindex_0500610C[] = {
    0x0001, 0x0000, 0x001E, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x001F, 0x0001, 0x0000,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0040,
    0x0001, 0x0000, 0x0001, 0x0000, 0x001E, 0x0022,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0021,
    0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0020,
};

// 0x05006154
static const struct Animation blargg_seg5_anim_05006154 = {
    0,
    0,
    0,
    0,
    0x1E,
    ANIMINDEX_NUMPARTS(blargg_seg5_animindex_0500610C),
    blargg_seg5_animvalue_05006088,
    blargg_seg5_animindex_0500610C,
    0,
    ANIM_FIELD_LENGTH(blargg_seg5_animvalue_05006088),
    ANIM_FIELD_LENGTH(blargg_seg5_animindex_0500610C),
};
