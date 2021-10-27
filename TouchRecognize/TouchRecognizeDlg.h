
// TouchRecognize.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#define DEF_1ST_ALGORITHM	0	/* 1st Algorith Test */
#define DEF_2ND_ALGORITHM	0	/* 2nd Algorith Test */
#define DEF_3RD_ALGORITHM	1	/* 3rd Algorith Test */
#define FEATURE_ALGORITH_PROCESS	DEF_3RD_ALGORITHM

/* Sub Point(First Region) Information */
/* Rectangle Data */
#define RECTANGLE_1ST_DIVISION1_X1		89u		/* �� */
#define RECTANGLE_1ST_DIVISION1_Y1		172u
#define RECTANGLE_1ST_DIVISION1_X2		318u
#define RECTANGLE_1ST_DIVISION1_Y2		172u
#define RECTANGLE_1ST_DIVISION1_X3		318u
#define RECTANGLE_1ST_DIVISION1_Y3		303u	/* 172 + 131 */		/* pc tool y axis -200 */
#define RECTANGLE_1ST_DIVISION1_X4		89u
#define RECTANGLE_1ST_DIVISION1_Y4		303u

#define RECTANGLE_1ST_DIVISION2_X1		89u
#define RECTANGLE_1ST_DIVISION2_Y1		303u
#define RECTANGLE_1ST_DIVISION2_X2		318u
#define RECTANGLE_1ST_DIVISION2_Y2		303u
#define RECTANGLE_1ST_DIVISION2_X3		318u
#define RECTANGLE_1ST_DIVISION2_Y3		434u	/* 172 + (131*2) */
#define RECTANGLE_1ST_DIVISION2_X4		89u
#define RECTANGLE_1ST_DIVISION2_Y4		434u

#define RECTANGLE_1ST_DIVISION3_X1		89u
#define RECTANGLE_1ST_DIVISION3_Y1		434u
#define RECTANGLE_1ST_DIVISION3_X2		318u
#define RECTANGLE_1ST_DIVISION3_Y2		434u
#define RECTANGLE_1ST_DIVISION3_X3		318u
#define RECTANGLE_1ST_DIVISION3_Y3		565u	/* 172 + (131*3) */
#define RECTANGLE_1ST_DIVISION3_X4		89u
#define RECTANGLE_1ST_DIVISION3_Y4		565u

#define RECTANGLE_1ST_DIVISION4_X1		89u
#define RECTANGLE_1ST_DIVISION4_Y1		565u
#define RECTANGLE_1ST_DIVISION4_X2		318u
#define RECTANGLE_1ST_DIVISION4_Y2		565u
#define RECTANGLE_1ST_DIVISION4_X3		318u
#define RECTANGLE_1ST_DIVISION4_Y3		696u	/* 172 + (131*4) */
#define RECTANGLE_1ST_DIVISION4_X4		89u
#define RECTANGLE_1ST_DIVISION4_Y4		696u

#define RECTANGLE_1ST_DIVISION5_X1		89u
#define RECTANGLE_1ST_DIVISION5_Y1		696u
#define RECTANGLE_1ST_DIVISION5_X2		318u
#define RECTANGLE_1ST_DIVISION5_Y2		696u
#define RECTANGLE_1ST_DIVISION5_X3		318u
#define RECTANGLE_1ST_DIVISION5_Y3		828u	/* 172 + (131*5) +1 */
#define RECTANGLE_1ST_DIVISION5_X4		89u
#define RECTANGLE_1ST_DIVISION5_Y4		828u

/* Sub Point(Second Region) Information */
/* 6point Polygon Data */
#define POLYGON6p_2ND_DIVISION1_X1		886u/2u	/* �� */	/* pc tool x axis -400  +  /2 */
#define POLYGON6p_2ND_DIVISION1_Y1		18u/2u					/* pc tool y axis -400 */
#define POLYGON6p_2ND_DIVISION1_X2		1243u/2u
#define POLYGON6p_2ND_DIVISION1_Y2		97u/2u
#define POLYGON6p_2ND_DIVISION1_X3		1529u/2u
#define POLYGON6p_2ND_DIVISION1_Y3		318u/2u
#define POLYGON6p_2ND_DIVISION1_X4		1346u/2u
#define POLYGON6p_2ND_DIVISION1_Y4		460u/2u
#define POLYGON6p_2ND_DIVISION1_X5		1141u/2u
#define POLYGON6p_2ND_DIVISION1_Y5		301u/2u
#define POLYGON6p_2ND_DIVISION1_X6		886u/2u
#define POLYGON6p_2ND_DIVISION1_Y6		245u/2u

#define POLYGON6p_2ND_DIVISION2_X1		1529u/2u	/* �� */
#define POLYGON6p_2ND_DIVISION2_Y1		318u/2u
#define POLYGON6p_2ND_DIVISION2_X2		1688u/2u
#define POLYGON6p_2ND_DIVISION2_Y2		638u/2u
#define POLYGON6p_2ND_DIVISION2_X3		1688u/2u
#define POLYGON6p_2ND_DIVISION2_Y3		993u/2u
#define POLYGON6p_2ND_DIVISION2_X4		1460u/2u
#define POLYGON6p_2ND_DIVISION2_Y4		943u/2u
#define POLYGON6p_2ND_DIVISION2_X5		1460u/2u
#define POLYGON6p_2ND_DIVISION2_Y5		689u/2u
#define POLYGON6p_2ND_DIVISION2_X6		1346u/2u
#define POLYGON6p_2ND_DIVISION2_Y6		460u/2u

#define POLYGON6p_2ND_DIVISION3_X1		1460u/2u	/*�� + ��*/
#define POLYGON6p_2ND_DIVISION3_Y1		943u/2u
#define POLYGON6p_2ND_DIVISION3_X2		1688u/2u
#define POLYGON6p_2ND_DIVISION3_Y2		993u/2u
#define POLYGON6p_2ND_DIVISION3_X3		1529u/2u
#define POLYGON6p_2ND_DIVISION3_Y3		1313u/2u
#define POLYGON6p_2ND_DIVISION3_X4		1243u/2u
#define POLYGON6p_2ND_DIVISION3_Y4		1534u/2u
#define POLYGON6p_2ND_DIVISION3_X5		1141u/2u
#define POLYGON6p_2ND_DIVISION3_Y5		1330u/2u
#define POLYGON6p_2ND_DIVISION3_X6		1346u/2u
#define POLYGON6p_2ND_DIVISION3_Y6		1172u/2u

#define POLYGON6p_2ND_DIVISION4_X1		631u/2u	/*�� + ��*/
#define POLYGON6p_2ND_DIVISION4_Y1		1330u/2u
#define POLYGON6p_2ND_DIVISION4_X2		886u/2u
#define POLYGON6p_2ND_DIVISION4_Y2		1386u/2u
#define POLYGON6p_2ND_DIVISION4_X3		1141u/2u
#define POLYGON6p_2ND_DIVISION4_Y3		1330u/2u
#define POLYGON6p_2ND_DIVISION4_X4		1243u/2u
#define POLYGON6p_2ND_DIVISION4_Y4		1534u/2u
#define POLYGON6p_2ND_DIVISION4_X5		886u/2u
#define POLYGON6p_2ND_DIVISION4_Y5		1613u/2u
#define POLYGON6p_2ND_DIVISION4_X6		529u/2u
#define POLYGON6p_2ND_DIVISION4_Y6		1534u/2u

#define POLYGON6p_2ND_DIVISION5_X1		85u/2u	/* �� */
#define POLYGON6p_2ND_DIVISION5_Y1		993u/2u
#define POLYGON6p_2ND_DIVISION5_X2		312u/2u
#define POLYGON6p_2ND_DIVISION5_Y2		943u/2u
#define POLYGON6p_2ND_DIVISION5_X3		426u/2u
#define POLYGON6p_2ND_DIVISION5_Y3		1172u/2u
#define POLYGON6p_2ND_DIVISION5_X4		631u/2u
#define POLYGON6p_2ND_DIVISION5_Y4		1330u/2u
#define POLYGON6p_2ND_DIVISION5_X5		529u/2u
#define POLYGON6p_2ND_DIVISION5_Y5		1534u/2u
#define POLYGON6p_2ND_DIVISION5_X6		243u/2u
#define POLYGON6p_2ND_DIVISION5_Y6		1313u/2u

#define POLYGON6p_2ND_DIVISION6_X1		243u/2u	/* �� */
#define POLYGON6p_2ND_DIVISION6_Y1		318u/2u
#define POLYGON6p_2ND_DIVISION6_X2		426u/2u
#define POLYGON6p_2ND_DIVISION6_Y2		460u/2u
#define POLYGON6p_2ND_DIVISION6_X3		312u/2u
#define POLYGON6p_2ND_DIVISION6_Y3		689u/2u
#define POLYGON6p_2ND_DIVISION6_X4		312u/2u
#define POLYGON6p_2ND_DIVISION6_Y4		943u/2u
#define POLYGON6p_2ND_DIVISION6_X5		85u/2u
#define POLYGON6p_2ND_DIVISION6_Y5		993u/2u
#define POLYGON6p_2ND_DIVISION6_X6		85u/2u
#define POLYGON6p_2ND_DIVISION6_Y6		638u/2u

#define POLYGON6p_2ND_DIVISION7_X1		529u/2u	/* �� */
#define POLYGON6p_2ND_DIVISION7_Y1		97u/2u
#define POLYGON6p_2ND_DIVISION7_X2		886u/2u
#define POLYGON6p_2ND_DIVISION7_Y2		18u/2u
#define POLYGON6p_2ND_DIVISION7_X3		886u/2u
#define POLYGON6p_2ND_DIVISION7_Y3		245u/2u
#define POLYGON6p_2ND_DIVISION7_X4		631u/2u
#define POLYGON6p_2ND_DIVISION7_Y4		301u/2u
#define POLYGON6p_2ND_DIVISION7_X5		426u/2u
#define POLYGON6p_2ND_DIVISION7_Y5		460u/2u
#define POLYGON6p_2ND_DIVISION7_X6		243u/2u
#define POLYGON6p_2ND_DIVISION7_Y6		318u/2u

/* Circle Data */
#define CIRCLE_2ND_MAIN_CENTER_X		1286u
#define CIRCLE_2ND_MAIN_CENTER_Y		816u
#define CIRCLE_2ND_MAIN_RADIUS_INSIDE	574u	/* 1860 - 1286 */
#define CIRCLE_2ND_MAIN_RADIUS_OUTSIDE	802u	/* 2088 - 1286 */

#define CIRCLE_2ND_DIVISION1_CENTER_X	158u						/* pc tool x axis -600 */
#define CIRCLE_2ND_DIVISION1_CENTER_Y	324u						/* pc tool y axis -1500 */
#define CIRCLE_2ND_DIVISION1_RADIUS		112u	/* 870 - 758 */

#define CIRCLE_2ND_DIVISION2_CENTER_X	686u
#define CIRCLE_2ND_DIVISION2_CENTER_Y	324u
#define CIRCLE_2ND_DIVISION2_RADIUS		122u	/* 1408 - 1286 */

#define CIRCLE_2ND_DIVISION3_CENTER_X	1214u
#define CIRCLE_2ND_DIVISION3_CENTER_Y	324u
#define CIRCLE_2ND_DIVISION3_RADIUS		127u	/* 1941 - 1814 */

/* Sub Point(Third Region) Information */
/* Rectangle Data */
#define RECTANGLE_3RD_DIVISION1_X1		292u 	/* �� */				/* pc tool x axis -2000 */
#define RECTANGLE_3RD_DIVISION1_Y1		113u
#define RECTANGLE_3RD_DIVISION1_X2		550u	/* 2292 + (258*1) */
#define RECTANGLE_3RD_DIVISION1_Y2		113u
#define RECTANGLE_3RD_DIVISION1_X3		550u
#define RECTANGLE_3RD_DIVISION1_Y3		335u
#define RECTANGLE_3RD_DIVISION1_X4		292u
#define RECTANGLE_3RD_DIVISION1_Y4		335u

#define RECTANGLE_3RD_DIVISION2_X1		550u
#define RECTANGLE_3RD_DIVISION2_Y1		113u
#define RECTANGLE_3RD_DIVISION2_X2		808u	/* 2292 + (258*2) */
#define RECTANGLE_3RD_DIVISION2_Y2		113u
#define RECTANGLE_3RD_DIVISION2_X3		808u
#define RECTANGLE_3RD_DIVISION2_Y3		335u
#define RECTANGLE_3RD_DIVISION2_X4		550u
#define RECTANGLE_3RD_DIVISION2_Y4		335u

#define RECTANGLE_3RD_DIVISION3_X1		808u
#define RECTANGLE_3RD_DIVISION3_Y1		113u
#define RECTANGLE_3RD_DIVISION3_X2		1068u	/* 2292 + (258*3) +2 */
#define RECTANGLE_3RD_DIVISION3_Y2		113u
#define RECTANGLE_3RD_DIVISION3_X3		1068u
#define RECTANGLE_3RD_DIVISION3_Y3		335u
#define RECTANGLE_3RD_DIVISION3_X4		808u
#define RECTANGLE_3RD_DIVISION3_Y4		335u

/* 6Point 1st Polygon Data */
#define POLYGON6p1st_3RD_DIVISION1_X1	680	/* ① */  /* pc tool x axis -2000 */
#define POLYGON6p1st_3RD_DIVISION1_Y1	59			   /* pc tool y axis -400 */
#define POLYGON6p1st_3RD_DIVISION1_X2	969
#define POLYGON6p1st_3RD_DIVISION1_Y2	150
#define POLYGON6p1st_3RD_DIVISION1_X3	1147
#define POLYGON6p1st_3RD_DIVISION1_Y3	388
#define POLYGON6p1st_3RD_DIVISION1_X4	970
#define POLYGON6p1st_3RD_DIVISION1_Y4	444
#define POLYGON6p1st_3RD_DIVISION1_X5	859
#define POLYGON6p1st_3RD_DIVISION1_Y5	296
#define POLYGON6p1st_3RD_DIVISION1_X6	680
#define POLYGON6p1st_3RD_DIVISION1_Y6	239

#define POLYGON6p1st_3RD_DIVISION2_X1	970u	/* ⑬ */
#define POLYGON6p1st_3RD_DIVISION2_Y1	444u
#define POLYGON6p1st_3RD_DIVISION2_X2	1147u
#define POLYGON6p1st_3RD_DIVISION2_Y2	388u
#define POLYGON6p1st_3RD_DIVISION2_X3	1147u
#define POLYGON6p1st_3RD_DIVISION2_Y3	683u
#define POLYGON6p1st_3RD_DIVISION2_X4	969u
#define POLYGON6p1st_3RD_DIVISION2_Y4	921u
#define POLYGON6p1st_3RD_DIVISION2_X5	859u
#define POLYGON6p1st_3RD_DIVISION2_Y5	775u
#define POLYGON6p1st_3RD_DIVISION2_X6	970u
#define POLYGON6p1st_3RD_DIVISION2_Y6	627u

#define POLYGON6p1st_3RD_DIVISION3_X1	500u 	/*⑮ + ②*/
#define POLYGON6p1st_3RD_DIVISION3_Y1	775u
#define POLYGON6p1st_3RD_DIVISION3_X2	680u
#define POLYGON6p1st_3RD_DIVISION3_Y2	832u
#define POLYGON6p1st_3RD_DIVISION3_X3	859u
#define POLYGON6p1st_3RD_DIVISION3_Y3	775u
#define POLYGON6p1st_3RD_DIVISION3_X4	969u
#define POLYGON6p1st_3RD_DIVISION3_Y4	921u
#define POLYGON6p1st_3RD_DIVISION3_X5	680u
#define POLYGON6p1st_3RD_DIVISION3_Y5	1012u
#define POLYGON6p1st_3RD_DIVISION3_X6	391u
#define POLYGON6p1st_3RD_DIVISION3_Y6	921u

#define POLYGON6p1st_3RD_DIVISION4_X1	212u	/* ⑨ */
#define POLYGON6p1st_3RD_DIVISION4_Y1	388u
#define POLYGON6p1st_3RD_DIVISION4_X2	389u
#define POLYGON6p1st_3RD_DIVISION4_Y2	444u
#define POLYGON6p1st_3RD_DIVISION4_X3	389u
#define POLYGON6p1st_3RD_DIVISION4_Y3	627u
#define POLYGON6p1st_3RD_DIVISION4_X4	500u
#define POLYGON6p1st_3RD_DIVISION4_Y4	775u
#define POLYGON6p1st_3RD_DIVISION4_X5	391u
#define POLYGON6p1st_3RD_DIVISION4_Y5	921u
#define POLYGON6p1st_3RD_DIVISION4_X6	212u
#define POLYGON6p1st_3RD_DIVISION4_Y6	683u

#define POLYGON6p1st_3RD_DIVISION5_X1	391u	/* ⑩ */
#define POLYGON6p1st_3RD_DIVISION5_Y1	150u
#define POLYGON6p1st_3RD_DIVISION5_X2	680u
#define POLYGON6p1st_3RD_DIVISION5_Y2	59u
#define POLYGON6p1st_3RD_DIVISION5_X3	680u
#define POLYGON6p1st_3RD_DIVISION5_Y3	239u
#define POLYGON6p1st_3RD_DIVISION5_X4	500u
#define POLYGON6p1st_3RD_DIVISION5_Y4	296u
#define POLYGON6p1st_3RD_DIVISION5_X5	389u
#define POLYGON6p1st_3RD_DIVISION5_Y5	444u
#define POLYGON6p1st_3RD_DIVISION5_X6	212u
#define POLYGON6p1st_3RD_DIVISION5_Y6	388u

/* 6Point 2nd Polygon Data */
#define POLYGON6p2nd_3RD_DIVISION1_X1	302u	/* �� */		/* pc tool x axis -2000 */
#define POLYGON6p2nd_3RD_DIVISION1_Y1	364u					/* pc tool y axis -1200 */
#define POLYGON6p2nd_3RD_DIVISION1_X2	347u
#define POLYGON6p2nd_3RD_DIVISION1_Y2	346u
#define POLYGON6p2nd_3RD_DIVISION1_X3	444u
#define POLYGON6p2nd_3RD_DIVISION1_Y3	415u
#define POLYGON6p2nd_3RD_DIVISION1_X4	556u
#define POLYGON6p2nd_3RD_DIVISION1_Y4	457u
#define POLYGON6p2nd_3RD_DIVISION1_X5	497u
#define POLYGON6p2nd_3RD_DIVISION1_Y5	633u
#define POLYGON6p2nd_3RD_DIVISION1_X6	357u
#define POLYGON6p2nd_3RD_DIVISION1_Y6	591u

#define POLYGON6p2nd_3RD_DIVISION2_X1	564u	/* �� */
#define POLYGON6p2nd_3RD_DIVISION2_Y1	459u
#define POLYGON6p2nd_3RD_DIVISION2_X2	796u
#define POLYGON6p2nd_3RD_DIVISION2_Y2	459u
#define POLYGON6p2nd_3RD_DIVISION2_X3	855u
#define POLYGON6p2nd_3RD_DIVISION2_Y3	637u
#define POLYGON6p2nd_3RD_DIVISION2_X4	822u
#define POLYGON6p2nd_3RD_DIVISION2_Y4	710u
#define POLYGON6p2nd_3RD_DIVISION2_X5	537u
#define POLYGON6p2nd_3RD_DIVISION2_Y5	710u
#define POLYGON6p2nd_3RD_DIVISION2_X6	505u
#define POLYGON6p2nd_3RD_DIVISION2_Y6	637u

#define POLYGON6p2nd_3RD_DIVISION3_X1	804u	/* �� */
#define POLYGON6p2nd_3RD_DIVISION3_Y1	457u
#define POLYGON6p2nd_3RD_DIVISION3_X2	916u
#define POLYGON6p2nd_3RD_DIVISION3_Y2	415u
#define POLYGON6p2nd_3RD_DIVISION3_X3	1013u
#define POLYGON6p2nd_3RD_DIVISION3_Y3	346u
#define POLYGON6p2nd_3RD_DIVISION3_X4	1058u
#define POLYGON6p2nd_3RD_DIVISION3_Y4	364u
#define POLYGON6p2nd_3RD_DIVISION3_X5	1003u
#define POLYGON6p2nd_3RD_DIVISION3_Y5	591u
#define POLYGON6p2nd_3RD_DIVISION3_X6	863u
#define POLYGON6p2nd_3RD_DIVISION3_Y6	633u

#if 1//kth_test1
#define POLYGON5p1rd_1RD_DIVISION1_X1	165/2
#define POLYGON5p1rd_1RD_DIVISION1_Y1	462
#define POLYGON5p1rd_1RD_DIVISION1_X2	220/2
#define POLYGON5p1rd_1RD_DIVISION1_Y2	325
#define POLYGON5p1rd_1RD_DIVISION1_X3	514/2
#define POLYGON5p1rd_1RD_DIVISION1_Y3	195
#define POLYGON5p1rd_1RD_DIVISION1_X4	514/2
#define POLYGON5p1rd_1RD_DIVISION1_Y4	405
#define POLYGON5p1rd_1RD_DIVISION1_X5	366/2
#define POLYGON5p1rd_1RD_DIVISION1_Y5	462

#define POLYGON5p1rd_1RD_DIVISION2_X1	514/2
#define POLYGON5p1rd_1RD_DIVISION2_Y1	405
#define POLYGON5p1rd_1RD_DIVISION2_X2	667/2
#define POLYGON5p1rd_1RD_DIVISION2_Y2	195
#define POLYGON5p1rd_1RD_DIVISION2_X3	827/2
#define POLYGON5p1rd_1RD_DIVISION2_Y3	88
#define POLYGON5p1rd_1RD_DIVISION2_X4	955/2
#define POLYGON5p1rd_1RD_DIVISION2_Y4	88
#define POLYGON5p1rd_1RD_DIVISION2_X5	955/2
#define POLYGON5p1rd_1RD_DIVISION2_Y5	319

#define POLYGON5p1rd_1RD_DIVISION3_X1	955/2
#define POLYGON5p1rd_1RD_DIVISION3_Y1	319
#define POLYGON5p1rd_1RD_DIVISION3_X2	1038/2
#define POLYGON5p1rd_1RD_DIVISION3_Y2	88
#define POLYGON5p1rd_1RD_DIVISION3_X3	1201/2
#define POLYGON5p1rd_1RD_DIVISION3_Y3	33
#define POLYGON5p1rd_1RD_DIVISION3_X4	1363/2
#define POLYGON5p1rd_1RD_DIVISION3_Y4	88
#define POLYGON5p1rd_1RD_DIVISION3_X5   1446/2
#define POLYGON5p1rd_1RD_DIVISION3_Y5	319

#define POLYGON5p1rd_1RD_DIVISION4_X1	1446/2
#define POLYGON5p1rd_1RD_DIVISION4_Y1	319
#define POLYGON5p1rd_1RD_DIVISION4_X2	1446/2
#define POLYGON5p1rd_1RD_DIVISION4_Y2	88
#define POLYGON5p1rd_1RD_DIVISION4_X3	1574/2
#define POLYGON5p1rd_1RD_DIVISION4_Y3	88
#define POLYGON5p1rd_1RD_DIVISION4_X4	1735/2
#define POLYGON5p1rd_1RD_DIVISION4_Y4	195
#define POLYGON5p1rd_1RD_DIVISION4_X5   1888/2
#define POLYGON5p1rd_1RD_DIVISION4_Y5	405 //319

#define POLYGON5p1rd_1RD_DIVISION5_X1	1888/2
#define POLYGON5p1rd_1RD_DIVISION5_Y1	405 //319
#define POLYGON5p1rd_1RD_DIVISION5_X2	1888/2
#define POLYGON5p1rd_1RD_DIVISION5_Y2	195
#define POLYGON5p1rd_1RD_DIVISION5_X3	2181/2
#define POLYGON5p1rd_1RD_DIVISION5_Y3	325
#define POLYGON5p1rd_1RD_DIVISION5_X4   2237/2
#define POLYGON5p1rd_1RD_DIVISION5_Y4	462
#define POLYGON5p1rd_1RD_DIVISION5_X5	2035/2
#define POLYGON5p1rd_1RD_DIVISION5_Y5	462


#define DEF_TOUCHDATA_BUF				4

#endif
typedef unsigned short  int         U16;
#if 1//kth_test1
typedef unsigned char               U07;
typedef signed char                 S07;
typedef volatile unsigned char      TIM08;
typedef char                        S08;
typedef unsigned char               U08;
typedef volatile unsigned short     TIM16;
typedef unsigned short  int         U15;
typedef signed   short  int         S15;
typedef unsigned long               U31;
typedef signed   long               S31;
typedef unsigned int                U32;
typedef int                			S32;
typedef double                      F64;
#endif
typedef enum {
	eDivisonState1 = 0u,
	eDivisonState2,
	eDivisonState3,
	eDivisonState4,
	eDivisonState5,
	eDivisonState6,
	eDivisonState7,
	eDivisonState8,
	eDivisonState9,
	eDivisonState10,
	eDivisonState11,
	eDivisonState12,
	eDivisonState13,
	eDivisonState14,
	eDivisonState15
} eDivisonState;

typedef enum {
	eAlgorithmType_1stRectangle = 0u,
	eAlgorithmType_2nd6pPolygon,
	eAlgorithmType_2ndCircle,
	eAlgorithmType_3rdRectangle,
	eAlgorithmType_3rd6pPolygon,
	eAlgorithmType_3rd5pPolygon,
#if 1//kth_test1
	eAlgorithmType_1rdCycleAlgorithm,
	eAlgorithmType_2rdCycleAlgorithm,
	eAlgorithmType_1rd5pPolygon
#endif
} eAlgorithmType;
#if 1//kth_test1
typedef enum {
	eDetecType_Unknown = 0u,
	eDetecType_Button,
	eDetecType_Scroll,
	eDetecType_Wheel
} eDetecType;
#endif
#pragma pack(1)
#if 1//kth_test1
typedef struct {
	BOOL bmatched;
	BOOL longkey;
	U08 region;
	U08 type;
	U08 division;
	U08 mode;
	U08 exact_region;
	U08 data[DEF_TOUCHDATA_BUF];
	U16 longkey_cnt;
	U16 longkeyconst_cnt;
	U32 matching_count;
	U32 iCrosses;
	U32 curr_data;
	U32 prev_data;
	U32 StartTimer;
	U32 match_data;
	F64 degree;
} s_DetectData;
#endif
typedef struct {
	int x;
	int y;
} s_Position;
#if 1
typedef struct {
	s_Position point[4];
} s_RectangleData;

typedef struct {
	s_Position point[6];
} s_Polygon6pData;

typedef struct {
	U16 center_x;
	U16 center_y;
	U16 radius;
} s_CircleData;
#else
typedef struct {
	s_Position point1;
	s_Position point2;
	s_Position point3;
	s_Position point4;
	s_Position point5;
	s_Position point6;
} s_Polygon6pData;
#endif

#pragma pack()
class CTouchRecognizeDlg : public CDialogEx
{
private:
	CRect m_rect;
	CPoint m_prev_pos;
	CPoint m_apnt[5];
	char m_is_clicked = 0;
	unsigned int iCrosses = 0; // unsigned로 임의로 바꿨다.
	BOOLEAN mouse_click = FALSE;
	BOOLEAN bStartFlag;
	eAlgorithmType AlgorithmTypeInfo;
	CComboBox mAlgorithmType;
	// 생성입니다.
public:
	CTouchRecognizeDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOUCHRECOGNIZE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	void DrawingData();

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCbnSelchangeAlgorithmCombo();
	int isLeft(CPoint P0, CPoint P1, CPoint P2);
	void CheckPointAndDisplay(CPoint point);
	//void CSetPoint(CPoint*, int order, int size); // 임의로 추가한 부분
	//CPoint CGetPoint(int order, int pointNumber); // 임의로 추가한 부분
	CStatic mStaticValue;
};