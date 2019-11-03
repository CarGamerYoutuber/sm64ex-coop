// SHARE_PATH: [level]/areas/1/1/, [level]/areas/1/2/, [level]/areas/1/3/, [level]/areas/1/4/

// 0x0E0006D4
const GeoLayout thi_geo_0006D4[] = {
   GEO_NODE_SCREEN_AREA(10, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT/2),
   GEO_OPEN_NODE(),
      GEO_ZBUFFER(0),
      GEO_OPEN_NODE(),
         GEO_NODE_ORTHO(100),
         GEO_OPEN_NODE(),
            GEO_BACKGROUND(BACKGROUND_OCEAN_SKY, geo_skybox_main),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
      GEO_ZBUFFER(1),
      GEO_OPEN_NODE(),
         GEO_CAMERA_FRUSTUM_WITH_FUNC(45, 100, 12800, geo_camera_fov),
         GEO_OPEN_NODE(),
            GEO_CAMERA(1, 0, 2000, 6000, 0, 0, 0, geo_camera_preset_and_pos),
            GEO_OPEN_NODE(),
               GEO_SCALE(0x00, 19660),
               GEO_OPEN_NODE(),
                  GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_seg7_dl_07005260),
                  GEO_DISPLAY_LIST(LAYER_OPAQUE, thi_seg7_dl_07006968),
                  GEO_DISPLAY_LIST(LAYER_ALPHA, thi_seg7_dl_07007008),
                  GEO_DISPLAY_LIST(LAYER_TRANSPARENT, thi_seg7_dl_070072E8),
               GEO_CLOSE_NODE(),
               GEO_DISPLAY_LIST(LAYER_TRANSPARENT_DECAL, thi_seg7_dl_07007538),
               GEO_ASM(   0, geo_movtex_pause_control),
               GEO_ASM(0x1302, geo_movtex_draw_water_regions),
               GEO_RENDER_OBJ(),
               GEO_ASM(   0, geo_enfvx_main),
            GEO_CLOSE_NODE(),
         GEO_CLOSE_NODE(),
      GEO_CLOSE_NODE(),
   GEO_CLOSE_NODE(),
   GEO_END(),
};
