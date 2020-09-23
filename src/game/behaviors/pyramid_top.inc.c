/**
 * Behaviors for bhvPyramidTop, bhvPyramidTopFragment, and
 * bhvPyramidPillarTouchDetector.
 *
 * bhvPyramidTop controls Shifting Sand Land's pyramid's top piece, which
 *      rotates and explodes when Mario stands on all four pillars.
 * bhvPyramidTopFragment controls the shards that the pyramid's top emits when
 *      it is spinning and exploding.
 * bhvPyramidPillarTouchDetector controls the intangible collision boxes that
 *      Mario touches when on top of each pillar.
 */

/**
 * Spawn the four pillars' touch detectors.
 */
void bhv_pyramid_top_init(void) {
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, 1789, 1024, 764, 0, 0,
                              0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, 1789, 896, -2579, 0, 0,
                              0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, -5883, 1024, -2579, 0, 0,
                              0);
    spawn_object_abs_with_rot(o, 0, MODEL_NONE, bhvPyramidPillarTouchDetector, -5883, 1024, 764, 0, 0,
                              0);
}

/**
 * Animate the pyramid top as rising and then spinning. Generate some pyramid
 * fragments in the process.
 */
void bhv_pyramid_top_spinning(void) {
    struct Object *pyramidFragment;

    // (TODO: What is this doing)
    o->oPosX = o->oHomeX + sins(o->oTimer * 0x4000) * 40.0f;

    // At first, move upward smoothly without rotating.
    if (o->oTimer < 60) {
        o->oPosY = o->oHomeY + absf_2(sins(o->oTimer * 0x2000) * 10.0f);
    } else {
        // Then, rotate at an accelerating rate, and move upward at a constant rate.
        o->oAngleVelYaw += 0x100;
        if (o->oAngleVelYaw > 0x1800) {
            o->oAngleVelYaw = 0x1800;
            o->oVelY = 5.0f;
        }

        o->oFaceAngleYaw += o->oAngleVelYaw;
        o->oPosY += o->oVelY;
    }

    // Every frame until 90 frames have passed, generate a pyramid fragment
    // with a random velocity and angle.
    if (o->oTimer < 90) {
        pyramidFragment = spawn_object(o, MODEL_DIRT_ANIMATION, bhvPyramidTopFragment);
        pyramidFragment->oForwardVel = random_float() * 10.0f + 20.0f;
        pyramidFragment->oMoveAngleYaw = random_u16();
        pyramidFragment->oPyramidTopFragmentsScale = 0.8f;
        pyramidFragment->oGravity = random_float() + 2.0f;
    }

    // After enough time, transition to the exploding state.
    if (o->oTimer == 150) {
        o->oAction = PYRAMID_TOP_ACT_EXPLODE;
    }
}

/**
 * Explode the pyramid top, generating dust and pyramid fragments.
 */
void bhv_pyramid_top_explode(void) {
    struct Object *pyramidFragment;
    s16 i;

    spawn_mist_particles_variable(0, 0, 690);

    // Generate 30 pyramid fragments with random properties.
    for (i = 0; i < 30; i++) {
        pyramidFragment = spawn_object(
            o, MODEL_DIRT_ANIMATION, bhvPyramidTopFragment
        );
        pyramidFragment->oForwardVel = random_float() * 50 + 80;
        pyramidFragment->oVelY = random_float() * 80 + 20;
        pyramidFragment->oMoveAngleYaw = random_u16();
        pyramidFragment->oPyramidTopFragmentsScale = 3;
        pyramidFragment->oGravity = random_float() * 2 + 5;
    }

    // Deactivate the pyramid top.
    o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
}

static u8 bhv_pyramid_top_ignore_if_true(void) {
    return (o->oAction != PYRAMID_TOP_ACT_SPINNING);
}

void bhv_pyramid_top_loop(void) {
    if (!network_sync_object_initialized(o)) {
        struct SyncObject* so = network_init_object(o, SYNC_DISTANCE_ONLY_EVENTS);
        so->ignore_if_true = bhv_pyramid_top_ignore_if_true;
        network_init_object_field(o, &o->oAction);
        network_init_object_field(o, &o->oPrevAction);
        network_init_object_field(o, &o->oTimer);
    }
    switch (o->oAction) {
        case PYRAMID_TOP_ACT_CHECK_IF_SOLVED:
            if (o->oPyramidTopPillarsTouched == 4) {
                play_puzzle_jingle();
                o->oAction = PYRAMID_TOP_ACT_SPINNING;
                network_send_object(o);
            }
            break;

        case PYRAMID_TOP_ACT_SPINNING:
            if (o->oTimer == 0) {
                cur_obj_play_sound_2(SOUND_GENERAL2_PYRAMID_TOP_SPIN);
            }

            bhv_pyramid_top_spinning();
            break;

        case PYRAMID_TOP_ACT_EXPLODE:
            if (o->oTimer == 0) {
                create_sound_spawner(SOUND_GENERAL2_PYRAMID_TOP_EXPLOSION);
            }

            bhv_pyramid_top_explode();
            break;
    }
}

/**
 * Initialize the pyramid fragment.
 */
void bhv_pyramid_top_fragment_init(void) {
    o->oFriction = 0.999f;
    o->oBuoyancy = 2.0f;
    o->oAnimState = 3;
    cur_obj_scale(o->oPyramidTopFragmentsScale);
}

/**
 * Rotate the pyramid fragment along the yaw and pitch axes. After some time,
 * deactivate it.
 */
void bhv_pyramid_top_fragment_loop(void) {
    object_step();
    o->oFaceAngleYaw += 0x1000;
    o->oFaceAnglePitch += 0x1000;

    if (o->oTimer == 60) {
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

/**
 * If Mario touches a pillar's touch detector, count it towards the pyramid
 * top's total count of touched detectors, and deactivate the detector.
 */
void bhv_pyramid_pillar_touch_detector_loop(void) {
    cur_obj_become_tangible();
    if ((o->oInteractStatus & INT_STATUS_INTERACTED) || obj_check_if_collided_with_object(o, gMarioStates[0].marioObj) == 1) {
        // Increase the pyramid top's count of pillars touched.
        o->parentObj->oPyramidTopPillarsTouched++;
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        if (!(o->oInteractStatus & INT_STATUS_INTERACTED)) {
            network_send_collect_item(o);
        }
    }
}
