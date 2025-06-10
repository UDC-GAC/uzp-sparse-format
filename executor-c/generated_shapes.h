#ifndef GENERATED_SHAPES_H
#define GENERATED_SHAPES_H

// Optimized loop for Shape#0
#define LOOP_SHAPE_0 \
    _Pragma("unroll") \
    for (int i = 0; i <= 4; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -7; \
    } \


// Optimized loop for Shape#1
#define LOOP_SHAPE_1 \
    _Pragma("unroll") \
    for (int i = 0; i <= 4; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 7; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#2
#define LOOP_SHAPE_2 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#3
#define LOOP_SHAPE_3 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 2; \
    } \


// Optimized loop for Shape#4
#define LOOP_SHAPE_4 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 0; \
        idx_x += 2; \
    } \


// Optimized loop for Shape#5
#define LOOP_SHAPE_5 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 2; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#6
#define LOOP_SHAPE_6 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 2; \
        idx_x += 0; \
    } \


// Optimized loop for Shape#7
#define LOOP_SHAPE_7 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 4; \
    } \


// Optimized loop for Shape#8
#define LOOP_SHAPE_8 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -4; \
    } \


// Optimized loop for Shape#9
#define LOOP_SHAPE_9 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 4; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#10
#define LOOP_SHAPE_10 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 4; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#11
#define LOOP_SHAPE_11 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -5; \
    } \


// Optimized loop for Shape#12
#define LOOP_SHAPE_12 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 5; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#13
#define LOOP_SHAPE_13 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 6; \
    } \


// Optimized loop for Shape#14
#define LOOP_SHAPE_14 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -6; \
    } \


// Optimized loop for Shape#15
#define LOOP_SHAPE_15 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 6; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#16
#define LOOP_SHAPE_16 \
    _Pragma("unroll") \
    for (int i = 0; i <= 3; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 6; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#17
#define LOOP_SHAPE_17 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 0; \
    } \


// Optimized loop for Shape#18
#define LOOP_SHAPE_18 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 0; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#19
#define LOOP_SHAPE_19 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#20
#define LOOP_SHAPE_20 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#21
#define LOOP_SHAPE_21 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 2; \
    } \


// Optimized loop for Shape#22
#define LOOP_SHAPE_22 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -2; \
    } \


// Optimized loop for Shape#23
#define LOOP_SHAPE_23 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 2; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#24
#define LOOP_SHAPE_24 \
    _Pragma("unroll") \
    for (int i = 0; i <= 2; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 2; \
        idx_x += -1; \
    } \


// Optimized loop for Shape#25
#define LOOP_SHAPE_25 \
    _Pragma("unroll") \
    for (int i = 0; i <= 1; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 0; \
    } \


// Optimized loop for Shape#26
#define LOOP_SHAPE_26 \
    _Pragma("unroll") \
    for (int i = 0; i <= 1; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 0; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#27
#define LOOP_SHAPE_27 \
    _Pragma("unroll") \
    for (int i = 0; i <= 1; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += 1; \
    } \


// Optimized loop for Shape#28
#define LOOP_SHAPE_28 \
    _Pragma("unroll") \
    for (int i = 0; i <= 1; i++) \
    { \
        /* Compute. */ \
        y[idx_y] += data_vector[a_data_pos++] * x[idx_x]; \
        idx_y += 1; \
        idx_x += -1; \
    } \


#define fundecl_run_shape_o2d_multitype(datatypename)                     \
static                                                                    \
inline                                                                    \
void run_shape_o2d_##datatypename(s_spf_structure_t* restrict spf_matrix, \
                                  s_origin_2d_t orig,                     \
                                  const datatypename* const restrict x,   \
                                  datatypename* restrict y)               \
{                                                                         \
    const datatypename* const data_vector = spf_matrix->data;             \
    long long idx_y = orig.coordinates[0];                                \
    long long idx_x = orig.coordinates[1];                                \
    int a_data_pos = orig.dataptr;                                        \
                                                                          \
    switch (orig.shape_id) {                                              \
        case 0: LOOP_SHAPE_0; break;                                \
        case 1: LOOP_SHAPE_1; break;                                \
        case 2: LOOP_SHAPE_2; break;                                \
        case 3: LOOP_SHAPE_3; break;                                \
        case 4: LOOP_SHAPE_4; break;                                \
        case 5: LOOP_SHAPE_5; break;                                \
        case 6: LOOP_SHAPE_6; break;                                \
        case 7: LOOP_SHAPE_7; break;                                \
        case 8: LOOP_SHAPE_8; break;                                \
        case 9: LOOP_SHAPE_9; break;                                \
        case 10: LOOP_SHAPE_10; break;                                \
        case 11: LOOP_SHAPE_11; break;                                \
        case 12: LOOP_SHAPE_12; break;                                \
        case 13: LOOP_SHAPE_13; break;                                \
        case 14: LOOP_SHAPE_14; break;                                \
        case 15: LOOP_SHAPE_15; break;                                \
        case 16: LOOP_SHAPE_16; break;                                \
        case 17: LOOP_SHAPE_17; break;                                \
        case 18: LOOP_SHAPE_18; break;                                \
        case 19: LOOP_SHAPE_19; break;                                \
        case 20: LOOP_SHAPE_20; break;                                \
        case 21: LOOP_SHAPE_21; break;                                \
        case 22: LOOP_SHAPE_22; break;                                \
        case 23: LOOP_SHAPE_23; break;                                \
        case 24: LOOP_SHAPE_24; break;                                \
        case 25: LOOP_SHAPE_25; break;                                \
        case 26: LOOP_SHAPE_26; break;                                \
        case 27: LOOP_SHAPE_27; break;                                \
        case 28: LOOP_SHAPE_28; break;                                \
        default: break;                                                   \
    }                                                                     \
}

#endif // GENERATED_SHAPES_H
