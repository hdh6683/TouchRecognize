#include "stdafx.h"
#include "TouchRecognize.h"
#include "TouchRecognizeDlg.h"
#include "afxdialogex.h"
#include <Windows.h> // 시간 재기 위해 include함
#if 1//kth_test1
#include <math.h>
#include <float.h>
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#define SEL_CIRCLE_ALGORITHM	1
#define SEL_RECTANGLE_ALGORITHM	1
#define SEL_POLYGON_RANGE	0
#define SEL_POLYGON_ALGORITHM 1
#define SEL_CYCLE_ALGORITHM	7 	// 0 ~ 8번 알고리즘이 존재한다

#define PI 3.141592653589f

#define TEST_COUNT 1000000
#define CIRCLE_TEST 0
#define RECTANGLE_TEST 0
#define POLYGON_TEST 0
#define CYCLE_TEST 0
#define SEL_DIVIDE 0
#define ABS_IS_LEFT 0


typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}node;

node* slopeTree;

// compare 구현
inline int compare(int middle, int searchnum);
inline int minus_compare(int middle, int searchnum);
int binsearch(int searchnum, int left, int right);
int minus_binsearch(int searchnum, int left, int right);
node* insert(node* root, int data);
inline int bintree_compare(int middle, int searchnum);
int bintree_search(int M);
inline int bintree_reverse_compare(int middle, int searchnum);
int bintree_reverse_search(int M);
#endif



node* insert(node* root, int data)
{
	if (root == NULL)
	{
		root = (node*)malloc(sizeof(node));
		root->right = root->left = NULL;
		root->data = data;
		return root;
	}
	else
	{
		if (data < root->data)
			root->left = insert(root->left, data);
		else
			root->right = insert(root->right, data);
	} return root;
}

const float t_CycleSlopeTable[10] = { // 사이클 기울기 테이블
	INFINITY,5.67128f,2.74748f,1.73205f,1.19175f,0.8391f,0.57735f,0.36397f,0.176327f,0
};

const int t_IntegerSlopeTable100[10] = { // 100배 정수값 사이클 기울기 테이블
	40000,567,275,173,119,84,58,36,18,0
};

const int t_SortedIntegerSlopeTable100[10] = { // 100배 정수값 사이클 기울기 테이블
	0,18,36,58,84,119,173,275,567,40000
};

const int t_IntegerSlopeTable1000[10] = { // 1000배 정수값 사이클 기울기 테이블
	400000,5671,2747,1732,1192,839,577,364,176,0
};

const int t_BinaryOrderTable[9][4] = {
	{4,1,0,-1}, {4,1,-1}, {4,1,2,-1}, {4,1,2,3}, {4,-1}, {4,7,5,-1}, {4,7,5,6}, {4,7,-1},{4,7,8,-1}
};

int t_BinaryResultTable[733][733];

//const s_Polygon6pData  t_3rdPolygon6p1stTable[eDivisonState6][6] =
const CPoint  t_1stRectangleTable[eDivisonState6][4] = {	//	[5][4] 배열
	{
		{RECTANGLE_1ST_DIVISION1_X1, RECTANGLE_1ST_DIVISION1_Y1}, {RECTANGLE_1ST_DIVISION1_X2, RECTANGLE_1ST_DIVISION1_Y2},//(89,172)(318,172)
		{RECTANGLE_1ST_DIVISION1_X3, RECTANGLE_1ST_DIVISION1_Y3}, {RECTANGLE_1ST_DIVISION1_X4, RECTANGLE_1ST_DIVISION1_Y4} //(318,303)(89,303)
	},
	{
		{RECTANGLE_1ST_DIVISION2_X1, RECTANGLE_1ST_DIVISION2_Y1}, {RECTANGLE_1ST_DIVISION2_X2, RECTANGLE_1ST_DIVISION2_Y2},
		{RECTANGLE_1ST_DIVISION2_X3, RECTANGLE_1ST_DIVISION2_Y3}, {RECTANGLE_1ST_DIVISION2_X4, RECTANGLE_1ST_DIVISION2_Y4}
	},
	{
		{RECTANGLE_1ST_DIVISION3_X1, RECTANGLE_1ST_DIVISION3_Y1}, {RECTANGLE_1ST_DIVISION3_X2, RECTANGLE_1ST_DIVISION3_Y2},
		{RECTANGLE_1ST_DIVISION3_X3, RECTANGLE_1ST_DIVISION3_Y3}, {RECTANGLE_1ST_DIVISION3_X4, RECTANGLE_1ST_DIVISION3_Y4}
	},
	{
		{RECTANGLE_1ST_DIVISION4_X1, RECTANGLE_1ST_DIVISION4_Y1}, {RECTANGLE_1ST_DIVISION4_X2, RECTANGLE_1ST_DIVISION4_Y2},
		{RECTANGLE_1ST_DIVISION4_X3, RECTANGLE_1ST_DIVISION4_Y3}, {RECTANGLE_1ST_DIVISION4_X4, RECTANGLE_1ST_DIVISION4_Y4}
	},
	{
		{RECTANGLE_1ST_DIVISION5_X1, RECTANGLE_1ST_DIVISION5_Y1}, {RECTANGLE_1ST_DIVISION5_X2, RECTANGLE_1ST_DIVISION5_Y2},
		{RECTANGLE_1ST_DIVISION5_X3, RECTANGLE_1ST_DIVISION5_Y3}, {RECTANGLE_1ST_DIVISION5_X4, RECTANGLE_1ST_DIVISION5_Y4}
	}
};

static const unsigned char Wave_Data0[] = {		//01_MEM_918B_48Khz_19.13m_(170h_0.5cle_5.04v)
	0x00, 0x01, 0x02, 0x7C, 0x03, 0x96, 0x7E, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19, 0x1B,
	0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x43,
	0x45, 0x47, 0x49, 0x4B, 0x4C, 0x4E, 0x50, 0x51, 0x53, 0x55, 0x56, 0x58, 0x59, 0x5B, 0x5C, 0x5E, 0x5F, 0x61, 0x62, 0x64,
	0x65, 0x66, 0x67, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x77, 0x78,
	0x79, 0x7A, 0x7A, 0x7B, 0x7B, 0x7C, 0x7C, 0x7D, 0x7D, 0x7D, 0x7E, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F,
	0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7D, 0x7C, 0x7C, 0x7C, 0x7B, 0x7A, 0x7A, 0x79, 0x79, 0x78, 0x77,
	0x76, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x69, 0x68, 0x67, 0x66, 0x64, 0x63, 0x62,
	0x60, 0x5F, 0x5D, 0x5C, 0x5A, 0x59, 0x57, 0x56, 0x54, 0x52, 0x51, 0x4F, 0x4D, 0x4C, 0x4A, 0x48, 0x46, 0x45, 0x43, 0x41,
	0x3F, 0x3D, 0x3B, 0x39, 0x37, 0x35, 0x33, 0x31, 0x2F, 0x2D, 0x2B, 0x29, 0x27, 0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19,
	0x16, 0x14, 0x12, 0x10, 0x0E, 0x0C, 0x0A, 0x07, 0x05, 0x03, 0x01, 0x00, 0xFD, 0xFB, 0xF9, 0xF7, 0xF5, 0xF3, 0xF1, 0xEE,
	0xEC, 0xEA, 0xE8, 0xE6, 0xE4, 0xE2, 0xE0, 0xDD, 0xDB, 0xD9, 0xD7, 0xD5, 0xD3, 0xD1, 0xCF, 0xCD, 0xCB, 0xC9, 0xC7, 0xC5,
	0xC3, 0xC1, 0xC0, 0xBE, 0xBC, 0xBA, 0xB8, 0xB7, 0xB5, 0xB3, 0xB1, 0xB0, 0xAE, 0xAC, 0xAB, 0xA9, 0xA8, 0xA6, 0xA4, 0xA3,
	0xA2, 0xA0, 0x9F, 0x9D, 0x9C, 0x9B, 0x99, 0x98, 0x97, 0x96, 0x94, 0x93, 0x92, 0x91, 0x90, 0x8F, 0x8E, 0x8D, 0x8C, 0x8B,
	0x8B, 0x8A, 0x89, 0x88, 0x88, 0x87, 0x86, 0x86, 0x85, 0x85, 0x84, 0x84, 0x83, 0x83, 0x82, 0x82, 0x82, 0x82, 0x81, 0x81,
	0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x82, 0x82, 0x83, 0x83, 0x83, 0x84, 0x84, 0x85, 0x85, 0x86,
	0x86, 0x87, 0x88, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x94, 0x95, 0x96, 0x97, 0x98,
	0x9A, 0x9B, 0x9C, 0x9E, 0x9F, 0xA0, 0xA2, 0xA3, 0xA5, 0xA6, 0xA8, 0xA9, 0xAB, 0xAD, 0xAE, 0xB0, 0xB2, 0xB3, 0xB5, 0xB7,
	0xB9, 0xBA, 0xBC, 0xBE, 0xC0, 0xC2, 0xC4, 0xC6, 0xC8, 0xC9, 0xCB, 0xCD, 0xCF, 0xD1, 0xD3, 0xD5, 0xD8, 0xDA, 0xDC, 0xDE,
	0xE0, 0xE2, 0xE4, 0xE6, 0xE8, 0xEA, 0xED, 0xEF, 0xF1, 0xF3, 0xF5, 0xF7, 0xF9, 0xFC, 0xFE, 0x00, 0x02, 0x04, 0x06, 0x08,
	0x0A, 0x0C, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32,
	0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40, 0x42, 0x43, 0x45, 0x47, 0x49, 0x4B, 0x4C, 0x4E, 0x50, 0x51, 0x53, 0x55, 0x56,
	0x58, 0x59, 0x5B, 0x5C, 0x5E, 0x5F, 0x61, 0x62, 0x64, 0x65, 0x66, 0x67, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70,
	0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x77, 0x78, 0x79, 0x7A, 0x7A, 0x7B, 0x7B, 0x7C, 0x7C, 0x7D, 0x7D, 0x7D, 0x7E,
	0x7E, 0x7E, 0x7E, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7D, 0x7C,
	0x7C, 0x7C, 0x7B, 0x7A, 0x7A, 0x79, 0x79, 0x78, 0x77, 0x76, 0x76, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D,
	0x6C, 0x6B, 0x69, 0x68, 0x67, 0x66, 0x64, 0x63, 0x62, 0x60, 0x5F, 0x5D, 0x5C, 0x5A, 0x59, 0x57, 0x56, 0x54, 0x52, 0x51,
	0x4F, 0x4D, 0x4C, 0x4A, 0x48, 0x46, 0x45, 0x43, 0x41, 0x3F, 0x3D, 0x3B, 0x39, 0x37, 0x35, 0x33, 0x31, 0x2F, 0x2D, 0x2B,
	0x29, 0x27, 0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19, 0x16, 0x14, 0x12, 0x10, 0x0E, 0x0C, 0x0A, 0x07, 0x05, 0x03, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0B, 0x0D, 0x0F, 0x11, 0x13, 0x15, 0x17, 0x19, 0x1B, 0x1D, 0x1F,
	0x21, 0x23, 0x25, 0x27, 0x29, 0x2B, 0x2D, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x39, 0x3B, 0x3D, 0x3F, 0x40, 0x42, 0x44,
	0x46, 0x47, 0x49, 0x4A, 0x4C, 0x4E, 0x4F, 0x51, 0x52, 0x54, 0x55, 0x57, 0x58, 0x5A, 0x5B, 0x5C, 0x5E, 0x5F, 0x60, 0x62,
	0x63, 0x64, 0x65, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x75, 0x76,
	0x77, 0x77, 0x78, 0x79, 0x79, 0x7A, 0x7A, 0x7B, 0x7B, 0x7C, 0x7C, 0x7D, 0x7D, 0x7D, 0x7E, 0x7E, 0x7E, 0x7E, 0x7F, 0x7F,
	0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7E, 0x7E, 0x7E, 0x7E, 0x7D, 0x7D, 0x7D, 0x7C, 0x7C, 0x7B, 0x7B,
	0x7A, 0x7A, 0x79, 0x79, 0x78, 0x77, 0x77, 0x76, 0x75, 0x75, 0x74, 0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B,
	0x6A, 0x69, 0x68, 0x67, 0x65, 0x64, 0x63, 0x62, 0x60, 0x5F, 0x5E, 0x5C, 0x5B, 0x5A, 0x58, 0x57, 0x55, 0x54, 0x52, 0x51,
	0x4F, 0x4E, 0x4C, 0x4A, 0x49, 0x47, 0x46, 0x44, 0x42, 0x40, 0x3F, 0x3D, 0x3B, 0x39, 0x38, 0x36, 0x34, 0x32, 0x30, 0x2E,
	0x2D, 0x2B, 0x29, 0x27, 0x25, 0x23, 0x21, 0x1F, 0x1D, 0x1B, 0x19, 0x17, 0x15, 0x13, 0x11, 0x0F, 0x0D, 0x0B, 0x0A, 0x08,
	0x06, 0x04, 0x02, 0x00, 0xFF, 0xFD, 0xFB, 0xF9, 0xF7, 0xF5, 0xF3, 0xF1, 0xEF, 0xED, 0xEB, 0xE9, 0xE7, 0xE5, 0xE3, 0xE1,
	0xE0, 0xDE, 0xDC, 0xDA, 0xD8, 0xD7, 0xD5, 0xD3, 0xD1, 0xD0, 0xCE, 0xCC, 0xCB, 0xC9, 0xC8, 0xC6, 0xC5, 0xC3, 0xC2, 0xC0,
	0xBF, 0xBE, 0xBC, 0xBB, 0xBA, 0xB9, 0xB8, 0xB6, 0xB5, 0xB4, 0xB3, 0xB2, 0xB1, 0xB0, 0xB0, 0xAF, 0xAE, 0xAD, 0xAD, 0xAC,
	0xAB, 0xAB, 0xAA, 0xAA, 0xA9, 0xA9, 0xA9, 0xA8, 0xA8, 0xA8, 0xA8, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA7, 0xA8, 0xA8, 0xA8,
	0xA8, 0xA8, 0xA9, 0xA9, 0xAA, 0xAA, 0xAB, 0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAF, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5,
	0xB6, 0xB7, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBF, 0xC0, 0xC2, 0xC3, 0xC4, 0xC6, 0xC7, 0xC9, 0xCB, 0xCC, 0xCE, 0xCF, 0xD1,
	0xD3, 0xD4, 0xD6, 0xD8, 0xDA, 0xDC, 0xDD, 0xDF, 0xE1, 0xE3, 0xE5, 0xE7, 0xE9, 0xEB, 0xEC, 0xEE, 0xF0, 0xF2, 0xF4, 0xF6,
	0xF8, 0xFA, 0xFC, 0xFE, 0x00,
};
/* Sub Point(Second Region) Information */
const CPoint  t_2ndPolygon6pTable[eDivisonState8][6] = {
	{
		{POLYGON6p_2ND_DIVISION1_X1, POLYGON6p_2ND_DIVISION1_Y1}, {POLYGON6p_2ND_DIVISION1_X2, POLYGON6p_2ND_DIVISION1_Y2},//(443,9)()
		{POLYGON6p_2ND_DIVISION1_X3, POLYGON6p_2ND_DIVISION1_Y3}, {POLYGON6p_2ND_DIVISION1_X4, POLYGON6p_2ND_DIVISION1_Y4},
		{POLYGON6p_2ND_DIVISION1_X5, POLYGON6p_2ND_DIVISION1_Y5}, {POLYGON6p_2ND_DIVISION1_X6, POLYGON6p_2ND_DIVISION1_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION2_X1, POLYGON6p_2ND_DIVISION2_Y1}, {POLYGON6p_2ND_DIVISION2_X2, POLYGON6p_2ND_DIVISION2_Y2},
		{POLYGON6p_2ND_DIVISION2_X3, POLYGON6p_2ND_DIVISION2_Y3}, {POLYGON6p_2ND_DIVISION2_X4, POLYGON6p_2ND_DIVISION2_Y4},
		{POLYGON6p_2ND_DIVISION2_X5, POLYGON6p_2ND_DIVISION2_Y5}, {POLYGON6p_2ND_DIVISION2_X6, POLYGON6p_2ND_DIVISION2_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION3_X1, POLYGON6p_2ND_DIVISION3_Y1}, {POLYGON6p_2ND_DIVISION3_X2, POLYGON6p_2ND_DIVISION3_Y2},
		{POLYGON6p_2ND_DIVISION3_X3, POLYGON6p_2ND_DIVISION3_Y3}, {POLYGON6p_2ND_DIVISION3_X4, POLYGON6p_2ND_DIVISION3_Y4},
		{POLYGON6p_2ND_DIVISION3_X5, POLYGON6p_2ND_DIVISION3_Y5}, {POLYGON6p_2ND_DIVISION3_X6, POLYGON6p_2ND_DIVISION3_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION4_X1, POLYGON6p_2ND_DIVISION4_Y1}, {POLYGON6p_2ND_DIVISION4_X2, POLYGON6p_2ND_DIVISION4_Y2},
		{POLYGON6p_2ND_DIVISION4_X3, POLYGON6p_2ND_DIVISION4_Y3}, {POLYGON6p_2ND_DIVISION4_X4, POLYGON6p_2ND_DIVISION4_Y4},
		{POLYGON6p_2ND_DIVISION4_X5, POLYGON6p_2ND_DIVISION4_Y5}, {POLYGON6p_2ND_DIVISION4_X6, POLYGON6p_2ND_DIVISION4_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION5_X1, POLYGON6p_2ND_DIVISION5_Y1}, {POLYGON6p_2ND_DIVISION5_X2, POLYGON6p_2ND_DIVISION5_Y2},
		{POLYGON6p_2ND_DIVISION5_X3, POLYGON6p_2ND_DIVISION5_Y3}, {POLYGON6p_2ND_DIVISION5_X4, POLYGON6p_2ND_DIVISION5_Y4},
		{POLYGON6p_2ND_DIVISION5_X5, POLYGON6p_2ND_DIVISION5_Y5}, {POLYGON6p_2ND_DIVISION5_X6, POLYGON6p_2ND_DIVISION5_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION6_X1, POLYGON6p_2ND_DIVISION6_Y1}, {POLYGON6p_2ND_DIVISION6_X2, POLYGON6p_2ND_DIVISION6_Y2},
		{POLYGON6p_2ND_DIVISION6_X3, POLYGON6p_2ND_DIVISION6_Y3}, {POLYGON6p_2ND_DIVISION6_X4, POLYGON6p_2ND_DIVISION6_Y4},
		{POLYGON6p_2ND_DIVISION6_X5, POLYGON6p_2ND_DIVISION6_Y5}, {POLYGON6p_2ND_DIVISION6_X6, POLYGON6p_2ND_DIVISION6_Y6}
	},
	{
		{POLYGON6p_2ND_DIVISION7_X1, POLYGON6p_2ND_DIVISION7_Y1}, {POLYGON6p_2ND_DIVISION7_X2, POLYGON6p_2ND_DIVISION7_Y2},
		{POLYGON6p_2ND_DIVISION7_X3, POLYGON6p_2ND_DIVISION7_Y3}, {POLYGON6p_2ND_DIVISION7_X4, POLYGON6p_2ND_DIVISION7_Y4},
		{POLYGON6p_2ND_DIVISION7_X5, POLYGON6p_2ND_DIVISION7_Y5}, {POLYGON6p_2ND_DIVISION7_X6, POLYGON6p_2ND_DIVISION7_Y6}
	}
};

const s_CircleData t_2ndCircleTable[eDivisonState4] = {	// 원의 중심과 그 반지름 선언
	{CIRCLE_2ND_DIVISION1_CENTER_X, CIRCLE_2ND_DIVISION1_CENTER_Y, CIRCLE_2ND_DIVISION1_RADIUS},
	{CIRCLE_2ND_DIVISION2_CENTER_X, CIRCLE_2ND_DIVISION2_CENTER_Y, CIRCLE_2ND_DIVISION2_RADIUS},
	{CIRCLE_2ND_DIVISION3_CENTER_X, CIRCLE_2ND_DIVISION3_CENTER_Y, CIRCLE_2ND_DIVISION3_RADIUS}
};

const s_CircleData SHO_CircleTable[] = {
	{ CIRCLE_2ND_DIVISION2_CENTER_X, CIRCLE_2ND_DIVISION2_CENTER_Y + 200, CIRCLE_2ND_DIVISION2_RADIUS * 3 },
};
/* Sub Point(Third Region) Information */
const CPoint  t_3rdRectangleTable[eDivisonState4][4] = {
	{
		{RECTANGLE_3RD_DIVISION1_X1, RECTANGLE_3RD_DIVISION1_Y1}, {RECTANGLE_3RD_DIVISION1_X2, RECTANGLE_3RD_DIVISION1_Y2},
		{RECTANGLE_3RD_DIVISION1_X3, RECTANGLE_3RD_DIVISION1_Y3}, {RECTANGLE_3RD_DIVISION1_X4, RECTANGLE_3RD_DIVISION1_Y4}
	},
	{
		{RECTANGLE_3RD_DIVISION2_X1, RECTANGLE_3RD_DIVISION2_Y1}, {RECTANGLE_3RD_DIVISION2_X2, RECTANGLE_3RD_DIVISION2_Y2},
		{RECTANGLE_3RD_DIVISION2_X3, RECTANGLE_3RD_DIVISION2_Y3}, {RECTANGLE_3RD_DIVISION2_X4, RECTANGLE_3RD_DIVISION2_Y4}
	},
	{
		{RECTANGLE_3RD_DIVISION3_X1, RECTANGLE_3RD_DIVISION3_Y1}, {RECTANGLE_3RD_DIVISION3_X2, RECTANGLE_3RD_DIVISION3_Y2},
		{RECTANGLE_3RD_DIVISION3_X3, RECTANGLE_3RD_DIVISION3_Y3}, {RECTANGLE_3RD_DIVISION3_X4, RECTANGLE_3RD_DIVISION3_Y4}
	}
};
#if 1//kth_test1
const s_CircleData t_1rdCycleAlgorithm[] = {
	{ CIRCLE_2ND_DIVISION2_CENTER_X, (CIRCLE_2ND_DIVISION2_CENTER_Y + 200), (CIRCLE_2ND_DIVISION2_RADIUS * 3)},
	{ CIRCLE_2ND_DIVISION2_CENTER_X, (CIRCLE_2ND_DIVISION2_CENTER_Y + 200), (CIRCLE_2ND_DIVISION2_RADIUS * 2)}
};
const s_CircleData t_2rdCycleAlgorithm[] = {
	{ CIRCLE_2ND_DIVISION2_CENTER_X, (CIRCLE_2ND_DIVISION2_CENTER_Y + 200), ((CIRCLE_2ND_DIVISION2_RADIUS * 4) + 30)},
	{ CIRCLE_2ND_DIVISION2_CENTER_X, (CIRCLE_2ND_DIVISION2_CENTER_Y + 200), ((CIRCLE_2ND_DIVISION2_RADIUS * 3) + 50)}
};

const CPoint  t_1rdPolygon5p1rdTable[eDivisonState6][5] = {
	{
		{ POLYGON5p1rd_1RD_DIVISION1_X1, POLYGON5p1rd_1RD_DIVISION1_Y1 }, { POLYGON5p1rd_1RD_DIVISION1_X2, POLYGON5p1rd_1RD_DIVISION1_Y2 },
		{ POLYGON5p1rd_1RD_DIVISION1_X3, POLYGON5p1rd_1RD_DIVISION1_Y3 }, { POLYGON5p1rd_1RD_DIVISION1_X4, POLYGON5p1rd_1RD_DIVISION1_Y4 },
		{ POLYGON5p1rd_1RD_DIVISION1_X5, POLYGON5p1rd_1RD_DIVISION1_Y5 }
	},
	{
		{ POLYGON5p1rd_1RD_DIVISION2_X1, POLYGON5p1rd_1RD_DIVISION2_Y1 }, { POLYGON5p1rd_1RD_DIVISION2_X2, POLYGON5p1rd_1RD_DIVISION2_Y2 },
		{ POLYGON5p1rd_1RD_DIVISION2_X3, POLYGON5p1rd_1RD_DIVISION2_Y3 }, { POLYGON5p1rd_1RD_DIVISION2_X4, POLYGON5p1rd_1RD_DIVISION2_Y4 },
		{ POLYGON5p1rd_1RD_DIVISION2_X5, POLYGON5p1rd_1RD_DIVISION2_Y5 }
	},
	{
		{ POLYGON5p1rd_1RD_DIVISION3_X1, POLYGON5p1rd_1RD_DIVISION3_Y1 }, { POLYGON5p1rd_1RD_DIVISION3_X2, POLYGON5p1rd_1RD_DIVISION3_Y2 },
		{ POLYGON5p1rd_1RD_DIVISION3_X3, POLYGON5p1rd_1RD_DIVISION3_Y3 }, { POLYGON5p1rd_1RD_DIVISION3_X4, POLYGON5p1rd_1RD_DIVISION3_Y4 },
		{ POLYGON5p1rd_1RD_DIVISION3_X5, POLYGON5p1rd_1RD_DIVISION3_Y5 }
	},
	{
		{ POLYGON5p1rd_1RD_DIVISION4_X1, POLYGON5p1rd_1RD_DIVISION4_Y1 }, { POLYGON5p1rd_1RD_DIVISION4_X2, POLYGON5p1rd_1RD_DIVISION4_Y2 },
		{ POLYGON5p1rd_1RD_DIVISION4_X3, POLYGON5p1rd_1RD_DIVISION4_Y3 }, { POLYGON5p1rd_1RD_DIVISION4_X4, POLYGON5p1rd_1RD_DIVISION4_Y4 },
		{ POLYGON5p1rd_1RD_DIVISION4_X5, POLYGON5p1rd_1RD_DIVISION4_Y5 }
	},
	{
		{ POLYGON5p1rd_1RD_DIVISION5_X1, POLYGON5p1rd_1RD_DIVISION5_Y1 }, { POLYGON5p1rd_1RD_DIVISION5_X2, POLYGON5p1rd_1RD_DIVISION5_Y2 },
		{ POLYGON5p1rd_1RD_DIVISION5_X3, POLYGON5p1rd_1RD_DIVISION5_Y3 }, { POLYGON5p1rd_1RD_DIVISION5_X4, POLYGON5p1rd_1RD_DIVISION5_Y4 },
		{ POLYGON5p1rd_1RD_DIVISION5_X5, POLYGON5p1rd_1RD_DIVISION5_Y5 }
	}
};

#endif
//winding number
const CPoint  t_3rdPolygon6p1stTable[eDivisonState6][6] = {
	{
		{ POLYGON6p1st_3RD_DIVISION1_X1, POLYGON6p1st_3RD_DIVISION1_Y1 }, { POLYGON6p1st_3RD_DIVISION1_X2, POLYGON6p1st_3RD_DIVISION1_Y2 },
		{ POLYGON6p1st_3RD_DIVISION1_X3, POLYGON6p1st_3RD_DIVISION1_Y3 }, { POLYGON6p1st_3RD_DIVISION1_X4, POLYGON6p1st_3RD_DIVISION1_Y4 },
		{ POLYGON6p1st_3RD_DIVISION1_X5, POLYGON6p1st_3RD_DIVISION1_Y5 }, { POLYGON6p1st_3RD_DIVISION1_X6, POLYGON6p1st_3RD_DIVISION1_Y6 }
	},
	{
		{ POLYGON6p1st_3RD_DIVISION2_X1, POLYGON6p1st_3RD_DIVISION2_Y1 }, { POLYGON6p1st_3RD_DIVISION2_X2, POLYGON6p1st_3RD_DIVISION2_Y2 },
		{ POLYGON6p1st_3RD_DIVISION2_X3, POLYGON6p1st_3RD_DIVISION2_Y3 }, { POLYGON6p1st_3RD_DIVISION2_X4, POLYGON6p1st_3RD_DIVISION2_Y4 },
		{ POLYGON6p1st_3RD_DIVISION2_X5, POLYGON6p1st_3RD_DIVISION2_Y5 }, { POLYGON6p1st_3RD_DIVISION2_X6, POLYGON6p1st_3RD_DIVISION2_Y6 }
	},
	{
		{ POLYGON6p1st_3RD_DIVISION3_X1, POLYGON6p1st_3RD_DIVISION3_Y1 }, { POLYGON6p1st_3RD_DIVISION3_X2, POLYGON6p1st_3RD_DIVISION3_Y2 },
		{ POLYGON6p1st_3RD_DIVISION3_X3, POLYGON6p1st_3RD_DIVISION3_Y3 }, { POLYGON6p1st_3RD_DIVISION3_X4, POLYGON6p1st_3RD_DIVISION3_Y4 },
		{ POLYGON6p1st_3RD_DIVISION3_X5, POLYGON6p1st_3RD_DIVISION3_Y5 }, { POLYGON6p1st_3RD_DIVISION3_X6, POLYGON6p1st_3RD_DIVISION3_Y6 }
	},
	{
		{ POLYGON6p1st_3RD_DIVISION4_X1, POLYGON6p1st_3RD_DIVISION4_Y1 }, { POLYGON6p1st_3RD_DIVISION4_X2, POLYGON6p1st_3RD_DIVISION4_Y2 },
		{ POLYGON6p1st_3RD_DIVISION4_X3, POLYGON6p1st_3RD_DIVISION4_Y3 }, { POLYGON6p1st_3RD_DIVISION4_X4, POLYGON6p1st_3RD_DIVISION4_Y4 },
		{ POLYGON6p1st_3RD_DIVISION4_X5, POLYGON6p1st_3RD_DIVISION4_Y5 }, { POLYGON6p1st_3RD_DIVISION4_X6, POLYGON6p1st_3RD_DIVISION4_Y6 }
	},
	{
		{ POLYGON6p1st_3RD_DIVISION5_X1, POLYGON6p1st_3RD_DIVISION5_Y1 }, { POLYGON6p1st_3RD_DIVISION5_X2, POLYGON6p1st_3RD_DIVISION5_Y2 },
		{ POLYGON6p1st_3RD_DIVISION5_X3, POLYGON6p1st_3RD_DIVISION5_Y3 }, { POLYGON6p1st_3RD_DIVISION5_X4, POLYGON6p1st_3RD_DIVISION5_Y4 },
		{ POLYGON6p1st_3RD_DIVISION5_X5, POLYGON6p1st_3RD_DIVISION5_Y5 }, { POLYGON6p1st_3RD_DIVISION5_X6, POLYGON6p1st_3RD_DIVISION5_Y6 }
	}
};

const CPoint  t_3rdPolygon6p2ndTable[eDivisonState4][6] = {
	{
		{POLYGON6p2nd_3RD_DIVISION1_X1, POLYGON6p2nd_3RD_DIVISION1_Y1}, {POLYGON6p2nd_3RD_DIVISION1_X2, POLYGON6p2nd_3RD_DIVISION1_Y2},
		{POLYGON6p2nd_3RD_DIVISION1_X3, POLYGON6p2nd_3RD_DIVISION1_Y3}, {POLYGON6p2nd_3RD_DIVISION1_X4, POLYGON6p2nd_3RD_DIVISION1_Y4},
		{POLYGON6p2nd_3RD_DIVISION1_X5, POLYGON6p2nd_3RD_DIVISION1_Y5}, {POLYGON6p2nd_3RD_DIVISION1_X6, POLYGON6p2nd_3RD_DIVISION1_Y6}
	},
	{
		{POLYGON6p2nd_3RD_DIVISION2_X1, POLYGON6p2nd_3RD_DIVISION2_Y1}, {POLYGON6p2nd_3RD_DIVISION2_X2, POLYGON6p2nd_3RD_DIVISION2_Y2},
		{POLYGON6p2nd_3RD_DIVISION2_X3, POLYGON6p2nd_3RD_DIVISION2_Y3}, {POLYGON6p2nd_3RD_DIVISION2_X4, POLYGON6p2nd_3RD_DIVISION2_Y4},
		{POLYGON6p2nd_3RD_DIVISION2_X5, POLYGON6p2nd_3RD_DIVISION2_Y5}, {POLYGON6p2nd_3RD_DIVISION2_X6, POLYGON6p2nd_3RD_DIVISION2_Y6}
	},
	{
		{POLYGON6p2nd_3RD_DIVISION3_X1, POLYGON6p2nd_3RD_DIVISION3_Y1}, {POLYGON6p2nd_3RD_DIVISION3_X2, POLYGON6p2nd_3RD_DIVISION3_Y2},
		{POLYGON6p2nd_3RD_DIVISION3_X3, POLYGON6p2nd_3RD_DIVISION3_Y3}, {POLYGON6p2nd_3RD_DIVISION3_X4, POLYGON6p2nd_3RD_DIVISION3_Y4},
		{POLYGON6p2nd_3RD_DIVISION3_X5, POLYGON6p2nd_3RD_DIVISION3_Y5}, {POLYGON6p2nd_3RD_DIVISION3_X6, POLYGON6p2nd_3RD_DIVISION3_Y6}
	}
};
#if 1//kth_test1
#define REGIONC1_CENTER_X				686u		//CIRCLE_2ND_DIVISION2_CENTER_X
#define REGIONC1_CENTER_Y				(324u+200u)	//(CIRCLE_2ND_DIVISION2_CENTER_Y + 200)
#define REGIONC1_4DIVSIZE				9u
#define REGIONC1_INNERRAD				244
#define REGIONC1_OUTERRAD				366
#define DEF_RADIAN						57.324 		//180/3.14
#define DEF_CHECK_TIME					1000000
static void DetectCtrl_SetDialDivision(U16 centerx, U16 centery, U16 innerradius, U16 outerradius, U08 size4div, const F64 refer_table[]);
static void DetectCtrl_GetAngleData(U16 centerx, U16 centery, U16 innerradius, U16 outerradius, int size4div, const F64 refer_table[]);
static s_Position m_PositionInfo;
static s_DetectData m_DetectDataInfo;
const F64 Gradient9[] = { 0, 0.17, 0.36, 0.57, 0.84, 1.19, 1.73, 2.74, 5.67, 1000 };
#else
static double DetectCtrl_SetDialDivision(U16 x, U16 y, U16 centerx, U16 centery, int size4div);
#endif

double  curr_data;

#if 1//kth_test1
static void DetectCtrl_SetDialDivision(U16 centerx, U16 centery, U16 innerradius, U16 outerradius, U08 size4div, const F64 refer_table[])
{
	U08 index;
	U08 temp;
	F64 gra = fabs(((F64)(m_PositionInfo.y - centery) / (m_PositionInfo.x - centerx)));
	U32 radius = (m_PositionInfo.x - centerx) * (m_PositionInfo.x - centerx) + (m_PositionInfo.y - centery) * (m_PositionInfo.y - centery);

	if ((radius > (U32)(innerradius * innerradius)) && (radius <= (U32)(outerradius * outerradius))) {
		if (m_PositionInfo.y == centery || m_PositionInfo.x == centerx) {
			if (m_DetectDataInfo.curr_data == 0) {
				if (m_PositionInfo.y == centery && m_PositionInfo.x > centerx) {
					m_DetectDataInfo.curr_data = 1;
				}
				else if (m_PositionInfo.y == centery && m_PositionInfo.x < centerx) {
					m_DetectDataInfo.curr_data = 1 + size4div * 2;
				}
				else if (m_PositionInfo.x == centerx && m_PositionInfo.y > centery) {
					m_DetectDataInfo.curr_data = 1 + size4div;
				}
				else if (m_PositionInfo.x == centerx && m_PositionInfo.y < centery) {
					m_DetectDataInfo.curr_data = 1 + size4div * 3;
				}

			}
			else {
				m_DetectDataInfo.curr_data = m_DetectDataInfo.curr_data;
			}
			m_DetectDataInfo.curr_data = 0xEE;
		}
		else {
			for (index = 0; index < size4div; index++) {
				if (gra > refer_table[index] && gra <= refer_table[index + 1]) {
					temp = index + 1;
					if (m_PositionInfo.x > centerx && m_PositionInfo.y > centery) {
						m_DetectDataInfo.curr_data = temp;
					}
					else if (m_PositionInfo.x < centerx && m_PositionInfo.y > centery) {
						m_DetectDataInfo.curr_data = 2 * size4div - index;
					}
					else if (m_PositionInfo.x < centerx && m_PositionInfo.y < centery) {
						m_DetectDataInfo.curr_data = 2 * size4div + temp;
					}
					else if (m_PositionInfo.x > centerx && m_PositionInfo.y < centery) {
						m_DetectDataInfo.curr_data = 4 * size4div - index;
					}
					m_DetectDataInfo.type = eDetecType_Wheel;
					if (m_DetectDataInfo.match_data == 0) {
						m_DetectDataInfo.match_data = m_DetectDataInfo.curr_data;
					}
					break;
				}
			}
		}
	}
	else {
		m_DetectDataInfo.curr_data = 0xFF;
	}
}
#else
static double DetectCtrl_SetDialDivision(U16 x, U16 y, U16 centerx, U16 centery, int size4div)
{
	int index = 0;
	int result = 0;
	double temp;
	double gra = fabs(((double)(y - centery) / (x - centerx)));
	int radius = (x - centerx) * (x - centerx) + (y - centery) * (y - centery);
	if (y == centery || x == centerx) {
		if (curr_data == 0) {
			if (y == centery && x > centerx) {						// 1번 영역 (1시방향)
				curr_data = 1;
			}
			else if (y == centery && x < centerx) {					// 19번 영역 (9시방향)
				curr_data = 19;
			}
			else if (x == centerx && y > centery) {					// 10번 영역 (6시방향)
				curr_data = 10;
			}
			else if (x == centerx && y < centery) {					// 28번 영역 (12시방향)
				curr_data = 28;
			}
		}
		else {
			curr_data = curr_data;
		}
	}
	else {
		for (index = 0; index < size4div; index++) {
			if (gra > refer_table[index] && gra <= refer_table[index + 1]) {
				temp = index + 1;
				curr_data = temp;
				if (x > centerx && y > centery) {
					curr_data = temp;
					break;
				}
				else if (x < centerx && y > centery) {
					curr_data = 2 * size4div - index;
					break;
				}
				else if (x < centerx && y < centery) {
					curr_data = 2 * size4div + temp;
					break;
				}
				else if (x > centerx && y < centery) {
					curr_data = 4 * size4div - index;
					break;
				}
			}
		}
	}
	return curr_data;
}
#endif

#if 1//kth_test1
static void DetectCtrl_GetAngleData(U16 centerx, U16 centery, U16 innerradius, U16 outerradius, int size4div, const F64 refer_table[])
{
	F64 degree_y = m_PositionInfo.y - centery;
	F64 degree_x = m_PositionInfo.x - centerx;
	U32 radius = (m_PositionInfo.x - centerx) * (m_PositionInfo.x - centerx) + (m_PositionInfo.y - centery) * (m_PositionInfo.y - centery);

	if ((radius > (U32)(innerradius * innerradius)) && (radius <= (U32)(outerradius * outerradius))) {
		m_DetectDataInfo.degree = atan2(degree_y, degree_x) * 180 / 3.1415;//)(F64)DEF_RADIAN;;
		if (m_DetectDataInfo.degree < 0.) {
			m_DetectDataInfo.degree = 360 + m_DetectDataInfo.degree;
		}
		//m_DetectDataInfo.degree = atan2f(degree_y, degree_x) * 180 / 3.1415f;
	}
	else {
		m_DetectDataInfo.degree = 0xFFFF;
	}
}
#endif

void ResizeComboBoxWnd(CComboBox& pCombo)
{
	CRect rctComboBox, rctDropDown;
	int itemsToShow = pCombo.GetCount();

	pCombo.GetClientRect(&rctComboBox); //Combo rect
	pCombo.GetDroppedControlRect(&rctDropDown); //DropDownList rect
	int itemHeight = pCombo.GetItemHeight(-1); //Get Item height
	pCombo.GetParent()->ScreenToClient(&rctDropDown); //Converts coordinates
	rctDropDown.bottom = rctDropDown.top + rctComboBox.Height() + itemHeight * itemsToShow; //Set height
	pCombo.MoveWindow(&rctDropDown);
}

CTouchRecognizeDlg::CTouchRecognizeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TOUCHRECOGNIZE_DIALOG, pParent)
#if 1//kth_test1
	, AlgorithmTypeInfo(eAlgorithmType_1rdCycleAlgorithm)
#else
	, AlgorithmTypeInfo(eAlgorithmType_1stRectangle)
#endif
	, bStartFlag(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_rect.SetRect(50, 50, 100, 100);
	//m_rect.SetRect(10, 10, 3200, 2000);

#if (SEL_CYCLE_ALGORITHM==7)
	unsigned int start_init_time;
	unsigned int end_init_time;

	start_init_time = GetTickCount64();

	// 이진 탐색 알고리즘 테이블 초기화
	int x, y, M, C2;
	float m;

	for (y = 158; y <= 890; y++) // 사이클의 y 좌표는 158 ~ 890
	{
		for (x = 320; x <= 1052; x++) // 사이클의 x 좌표는 320 ~ 1052
		{
#if 1
			C2 = ((x - t_1rdCycleAlgorithm[0].center_x) * (x - t_1rdCycleAlgorithm[0].center_x))
				+ ((y - t_1rdCycleAlgorithm[0].center_y) * (y - t_1rdCycleAlgorithm[0].center_y)); // C² = A² + B²

			if ((C2 <= (t_1rdCycleAlgorithm[0].radius * t_1rdCycleAlgorithm[0].radius))
				&& (C2 >= (t_1rdCycleAlgorithm[1].radius * t_1rdCycleAlgorithm[1].radius))) // r² < C² < R²이면 원 안에 있다.
#endif
			{
				// 이진 탐색 기법 사용
				m = (float)(t_1rdCycleAlgorithm[0].center_y - y) / (float)(x - t_1rdCycleAlgorithm[0].center_x);
				M = m * 100;

				if (x > t_1rdCycleAlgorithm[0].center_x)
				{
					if (y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						//areaSelect = binsearch(M, 0, 9);
						t_BinaryResultTable[x - 320][y - 158] = binsearch(M, 0, 9);
					}
					else
					{
						//4사분면
						//areaSelect = minus_binsearch(-M, 0, 9) + 9;
						t_BinaryResultTable[x - 320][y - 158] = minus_binsearch(-M, 0, 9) + 9;
					}
				}
				else
				{
					if (y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						//areaSelect = minus_binsearch(-M, 0, 9) + 27;
						t_BinaryResultTable[x - 320][y - 158] = minus_binsearch(-M, 0, 9) + 27;
					}
					else
					{
						//3사분면
						//areaSelect = binsearch(M, 0, 9) + 18;
						t_BinaryResultTable[x - 320][y - 158] = binsearch(M, 0, 9) + 18;
					}
				}
			}
#if 1
			else
			{
				t_BinaryResultTable[x - 320][y - 158] = -1;
			}
#endif
		}
	}

	end_init_time = GetTickCount64();
	//display_text.Format(_T("이진 탐색 알고리즘 테이블 초기화 끝!\n경과시간 : %dms"), end_init_time - start_init_time);
	//SetDlgItemText(IDC_STATIC_VALUE, display_text);
	// 이진 탐색 알고리즘 테이블 초기화 끝
	init_time = end_init_time - start_init_time;

#elif (SEL_CYCLE_ALGORITHM==8)

	slopeTree = insert(slopeTree, 4);
	slopeTree = insert(slopeTree, 1);
	slopeTree = insert(slopeTree, 0);
	slopeTree = insert(slopeTree, 2);
	slopeTree = insert(slopeTree, 3);
	slopeTree = insert(slopeTree, 7);
	slopeTree = insert(slopeTree, 5);
	slopeTree = insert(slopeTree, 8);
	slopeTree = insert(slopeTree, 6);

#endif

}

void CTouchRecognizeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_VALUE, mStaticValue);
	DDX_Control(pDX, IDC_ALGORITHM_COMBO, mAlgorithmType);
}

BEGIN_MESSAGE_MAP(CTouchRecognizeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_CBN_SELCHANGE(IDC_ALGORITHM_COMBO, &CTouchRecognizeDlg::OnCbnSelchangeAlgorithmCombo)
END_MESSAGE_MAP()

BOOL CTouchRecognizeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	SetDlgItemText(IDC_STATIC_VALUE, _T("Unknown"));
	return TRUE;
}

void CTouchRecognizeDlg::DrawingData()
{
	int idx = 0;
	CPaintDC dc(this);
	switch (AlgorithmTypeInfo) {
	case eAlgorithmType_1stRectangle:
		for (; idx < eDivisonState6; idx++) {
			dc.Polygon(&t_1stRectangleTable[idx][0], 4);
		}
		break;
	case eAlgorithmType_2nd6pPolygon:
		for (; idx < eDivisonState8; idx++) {
			dc.Polygon(&t_2ndPolygon6pTable[idx][0], 6);
		}
		break;
	case eAlgorithmType_2ndCircle:
		for (; idx < eDivisonState4; idx++) {
			dc.Ellipse((t_2ndCircleTable[idx].center_x - t_2ndCircleTable[idx].radius), (t_2ndCircleTable[idx].center_y - t_2ndCircleTable[idx].radius)
				, (t_2ndCircleTable[idx].center_x + t_2ndCircleTable[idx].radius), (t_2ndCircleTable[idx].center_y + t_2ndCircleTable[idx].radius));
		}
		break;
	case eAlgorithmType_3rdRectangle:
		for (; idx < eDivisonState4; idx++) {
			dc.Polygon(&t_3rdRectangleTable[idx][0], 4);
		}
		break;
	case eAlgorithmType_3rd6pPolygon:
#if (FEATURE_ALGORITH_PROCESS == DEF_3RD_ALGORITHM)
		for (; idx < eDivisonState6; idx++) {
			dc.Polygon(&t_3rdPolygon6p1stTable[idx][0], 6);
		}
#endif
		break;
	case eAlgorithmType_3rd5pPolygon:
		for (; idx < eDivisonState4; idx++) {
			dc.Polygon(&t_3rdPolygon6p2ndTable[idx][0], 6);
		}
		break;

#if 1//kth_test1
	case eAlgorithmType_1rdCycleAlgorithm:
		for (; idx < eDivisonState3; idx++) {
			dc.Ellipse((t_1rdCycleAlgorithm[idx].center_x - t_1rdCycleAlgorithm[idx].radius), (t_1rdCycleAlgorithm[idx].center_y - t_1rdCycleAlgorithm[idx].radius)
				, (t_1rdCycleAlgorithm[idx].center_x + t_1rdCycleAlgorithm[idx].radius), (t_1rdCycleAlgorithm[idx].center_y + t_1rdCycleAlgorithm[idx].radius));
			if (idx == 0) {
				dc.MoveTo((t_1rdCycleAlgorithm[idx].center_x - t_1rdCycleAlgorithm[idx].radius), t_1rdCycleAlgorithm[idx].center_y);
				dc.LineTo((t_1rdCycleAlgorithm[idx].center_x + t_1rdCycleAlgorithm[idx].radius), t_1rdCycleAlgorithm[idx].center_y);
				dc.MoveTo((t_1rdCycleAlgorithm[idx].center_x), t_1rdCycleAlgorithm[idx].center_y - t_1rdCycleAlgorithm[idx].radius);
				dc.LineTo((t_1rdCycleAlgorithm[idx].center_x), t_1rdCycleAlgorithm[idx].center_y + t_1rdCycleAlgorithm[idx].radius);
			}
		}
		break;
	case eAlgorithmType_2rdCycleAlgorithm:
		for (; idx < eDivisonState3; idx++) {
			dc.Ellipse((t_2rdCycleAlgorithm[idx].center_x - t_2rdCycleAlgorithm[idx].radius), (t_2rdCycleAlgorithm[idx].center_y - t_2rdCycleAlgorithm[idx].radius)
				, (t_2rdCycleAlgorithm[idx].center_x + t_2rdCycleAlgorithm[idx].radius), (t_2rdCycleAlgorithm[idx].center_y + t_2rdCycleAlgorithm[idx].radius));
		}
		dc.Rectangle((CIRCLE_2ND_DIVISION2_CENTER_X - (CIRCLE_2ND_DIVISION2_RADIUS * 3)), ((CIRCLE_2ND_DIVISION2_CENTER_Y + 200) - (CIRCLE_2ND_DIVISION2_RADIUS * 3))
			, (CIRCLE_2ND_DIVISION2_CENTER_X + (CIRCLE_2ND_DIVISION2_RADIUS * 3)), ((CIRCLE_2ND_DIVISION2_CENTER_Y + 200) + (CIRCLE_2ND_DIVISION2_RADIUS * 3)));
		break;
	case eAlgorithmType_1rd5pPolygon:
		for (; idx < eDivisonState6; idx++) {
			dc.Polygon(&t_1rdPolygon5p1rdTable[idx][0], 5);
		}
		break;
#else
	case eAlgorithmType_1rdCycleAlgorithm:
		//for (; idx < eDivisonState4; idx++)
	{
		dc.Ellipse((SHO_CircleTable[0].center_x - SHO_CircleTable[0].radius), (SHO_CircleTable[0].center_y - SHO_CircleTable[0].radius)
			, (SHO_CircleTable[0].center_x + SHO_CircleTable[0].radius), (SHO_CircleTable[0].center_y + SHO_CircleTable[0].radius));
	}
	break;
#endif

	default: break;
	}
}


void CTouchRecognizeDlg::OnPaint()
{
	CPaintDC dc(this);
	if (IsIconic()) {
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		//if(AlgorithmTypeInfo != (eAlgorithmType)mAlgorithmType.GetCurSel())
		{
			Invalidate();
			if (bStartFlag) {
				AlgorithmTypeInfo = (eAlgorithmType)mAlgorithmType.GetCurSel();
			}
			else {

				bStartFlag = TRUE;
			}
			mAlgorithmType.SetCurSel(AlgorithmTypeInfo);
			ResizeComboBoxWnd(mAlgorithmType);
			DrawingData();
		}
		// CDialogEx::OnPaint();
	}
}

HCURSOR CTouchRecognizeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTouchRecognizeDlg::OnLButtonDown(UINT nFlags, CPoint point)				// 왼쪽 마우스 버튼 누를때 이벤트 발생
{
	mouse_click = TRUE;
	if (m_rect.PtInRect(point)) {
		m_is_clicked = 1;
#if 0//kth_test
		m_prev_pos = point;
		SetCapture();
#endif
	}

	CheckPointAndDisplay(point);

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CTouchRecognizeDlg::OnLButtonUp(UINT nFlags, CPoint point)					// 왼쪽 마우스 버튼 땔때 이벤트 발생
{
	mouse_click = FALSE;
	curr_data = 0;
	SetDlgItemText(IDC_STATIC_VALUE, _T("Unknown"));
	if (m_is_clicked == 1) {
		m_is_clicked = 0;
#if 0//kth_test
		ReleaseCapture();
#endif
	}
#if 1//kth_test1
	(void)memset(&m_PositionInfo, 0x0, sizeof(s_Position));
	(void)memset(&m_DetectDataInfo, 0x0, sizeof(s_DetectData));
#endif
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CTouchRecognizeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mouse_click) {
		CheckPointAndDisplay(point);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}


void CTouchRecognizeDlg::OnCbnSelchangeAlgorithmCombo()
{
	//AlgorithmTypeInfo = (eAlgorithmType)mAlgorithmType.GetCurSel();
	Invalidate();
	UpdateData(TRUE);
}

inline int CTouchRecognizeDlg::isLeft(CPoint P0, CPoint P1, CPoint P2)
{
#if (ABS_IS_LEFT==0)
	return ((P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y));
	//return result;
#else
	return (abs(P1.x - P0.x) * abs(P2.y - P0.y)) - (abs(P2.x - P0.x) * abs(P1.y - P0.y));
#endif
}


void CTouchRecognizeDlg::CheckPointAndDisplay(CPoint point)
{
	CString display_text;
	BOOL is_in;
	float interSection;
	int presentX;
	int optInterSection;
	int D;
	int j;
	int C2;
	unsigned int idxSelect;
	unsigned int start_time, end_time;

	// To-Do
	switch (AlgorithmTypeInfo) {
	case eAlgorithmType_1stRectangle:

#if (RECTANGLE_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{
			// i. 범위 사각형 알고리즘
			if ((point.x >= (t_1stRectangleTable[0][0]).x) && (point.x <= (t_1stRectangleTable[0][1]).x)
				&& (point.y >= (t_1stRectangleTable[0][0]).y) && (point.y < (t_1stRectangleTable[4][2]).y))// 터치가 범위 안에 있을 경우
			{
#if (SEL_RECTANGLE_ALGORITHM==0)	// i-1. original 범위 사각형 알고리즘
				for (int i = 0; i < 5; i++)
				{
					if ((point.y >= (t_1stRectangleTable[i][0]).y) && (point.y < (t_1stRectangleTable[i][2]).y))
					{
						//SetDlgItemText(IDC_STATIC_VALUE, _T("i번 칸 터치"));
						idxSelect = i;
#if (RECTANGLE_TEST!=1)
						display_text.Format(_T("idx=%d Inside"), idxSelect);
#endif
						break;
					}
				}

#else	// ii. optimized 범위 사각형 알고리즘
				// (최대 y좌표 - 현재 y좌표)/(사각형 한칸의 y좌표 범위)
				idxSelect = (point.y - t_1stRectangleTable[0][0].y) / (t_1stRectangleTable[4][2].y - t_1stRectangleTable[3][2].y);
#if (RECTANGLE_TEST!=1)
				display_text.Format(_T("idx=%d Inside"), idxSelect);
#endif
#if 0
				switch (idxSelect)
				{
				case 0:
					idxSelect = 4;

					break;
				case 1:
					idxSelect = 3;
					display_text.Format(_T("idx=%d Inside"), idxSelect);
					break;
				case 2:
					idxSelect = 2;
					display_text.Format(_T("idx=%d Inside"), idxSelect);
					break;
				case 3:
					idxSelect = 1;
					display_text.Format(_T("idx=%d Inside"), idxSelect);
					break;
				case 4:
					idxSelect = 0;
					display_text.Format(_T("idx=%d Inside"), idxSelect);
					break;
				}
#endif
#endif
			}
			else// 터치가 범위 안에 없을 경우
			{
				display_text.Format(_T("Outside"));
			}
			// 범위 사각형 알고리즘 끝
		}
#if (RECTANGLE_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("idx : %u, %dms"), idxSelect, end_time - start_time);
#endif

		// DlgItemText 표시
		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	case eAlgorithmType_2nd6pPolygon:

#if (POLYGON_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{
			is_in = FALSE; // 점이 다각형 안에 있는지?
			//float interSection;
			//int j;
			// int iCrosses = 0; // 교차 횟수 
#if (SEL_POLYGON_RANGE==1)
			if (((t_2ndPolygon6pTable[0][0].y <= point.y) && (t_2ndPolygon6pTable[4][4].y >= point.y))
				&& ((t_2ndPolygon6pTable[1][1].x >= point.x) && (t_2ndPolygon6pTable[5][4].x <= point.x)))
#endif
			{
				for (int n = 0; n < 7; n++) // 7개의 다각형이 있다.
				{
					iCrosses = 0;
					for (int i = 0; i < 6; i++) // 육각형이다.
					{
						j = (i + 1) % 6; 
						//점이 선분(t_2ndPolygon6pTable[n][i] ~ t_2ndPolygon6pTable[n][j])의 y좌표 사이에 있다.
#if (SEL_POLYGON_ALGORITHM==2)
//    isLeft: >0 for P2  선분 왼쪽
//            =0 for P2  선분 위
//            <0 for P2  선분 오른쪽
						if (t_2ndPolygon6pTable[n][i].y <= point.y) 
						{
							if (t_2ndPolygon6pTable[n][j].y > point.y)
							{
								if (isLeft(t_2ndPolygon6pTable[n][i], t_2ndPolygon6pTable[n][j], point) > 0)
								{
									iCrosses++;
								}
							}
						}
						else 
						{
							if (t_2ndPolygon6pTable[n][j].y <= point.y)
							{
								if (isLeft(t_2ndPolygon6pTable[n][i], t_2ndPolygon6pTable[n][j], point) < 0)
								{
									iCrosses--;
								}
							}
						}
#endif
						// interSection는 점을 지나는 수평선과 선분(t_2ndPolygon6pTable[n][i] ~ t_2ndPolygon6pTable[n][j])의 교점 
#if (SEL_POLYGON_ALGORITHM==0||SEL_POLYGON_ALGORITHM==1)
						if ((t_2ndPolygon6pTable[n][i].y > point.y) != (t_2ndPolygon6pTable[n][j].y > point.y)) // 선분을 이루는 두 점의 y좌표가 수평선을 중간에 둔다.
#endif
						{
#if (SEL_POLYGON_ALGORITHM==0)
							interSection =
								(((float)(t_2ndPolygon6pTable[n][j].x - t_2ndPolygon6pTable[n][i].x) / (float)(t_2ndPolygon6pTable[n][j].y - t_2ndPolygon6pTable[n][i].y))
									* (float)(point.y - t_2ndPolygon6pTable[n][i].y)) // 기울기의 역수와 y좌표의 변화값을 곱하면 x좌표의 변화값이 나온다
								+ (float)t_2ndPolygon6pTable[n][i].x; //
							if (point.x < interSection) iCrosses++; // interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 
#elif (SEL_POLYGON_ALGORITHM==1)
#if (SEL_DIVIDE==0)
							optInterSection =
								(t_2ndPolygon6pTable[n][j].x - t_2ndPolygon6pTable[n][i].x) * (point.y - t_2ndPolygon6pTable[n][i].y);

							presentX = (point.x - t_2ndPolygon6pTable[n][i].x) * (t_2ndPolygon6pTable[n][j].y - t_2ndPolygon6pTable[n][i].y);

#else
							optInterSection =
								(t_2ndPolygon6pTable[n][j].x - t_2ndPolygon6pTable[n][i].x) * (point.y - t_2ndPolygon6pTable[n][i].y)
								/ (t_2ndPolygon6pTable[n][j].y - t_2ndPolygon6pTable[n][i].y);

							presentX = (point.x - t_2ndPolygon6pTable[n][i].x);
#endif

							// 양수 음수 판별 최적화
#if (SEL_DIVIDE==0)
							if ((t_2ndPolygon6pTable[n][j].y - t_2ndPolygon6pTable[n][i].y) < 0)
							{
								if (presentX > optInterSection)
								{
									iCrosses++;
								}
							}
							else
							{
								if (presentX < optInterSection)
								{
									iCrosses++;
								}
							}
#else
							if (presentX < optInterSection)
							{
								iCrosses++;
							}// interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 
#endif

#endif
						}

					}

					// 홀수면 내부, 짝수면 외부에 있음 
					if ((iCrosses & 0x01) == 1) // (iCrosses % 2) == 1
					{
						//bPointInPolygon = TRUE;
						is_in = TRUE;
						idxSelect = n;
#if (POLYGON_TEST!=1)
						display_text.Format(_T("idx=%d,cross=%d (%d,%d) Inside"), idxSelect, iCrosses, point.x, point.y);
#endif
						break;
					}
				}
			}

			if (is_in == FALSE)
			{
				display_text.Format(_T("(%d,%d) Outside cross=%d"), point.x, point.y, iCrosses);
			}
		}
#if (POLYGON_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("idx : %d, %dms"), idxSelect, end_time - start_time);
#endif

		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	case eAlgorithmType_2ndCircle:
		// 시간 측정


#if (CIRCLE_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{
			is_in = FALSE;
#if (SEL_CIRCLE_ALGORITHM==0)
			if (((point.x >= (158-112)) && (point.x < (158+112)))
				|| ((point.x >= (686 - 122)) && (point.x < (686+122))) 
				|| ((point.x >= (1214 - 127)) && (point.x < (1214+127))))// 터치가 원의 x좌표 범위 안에 있을 경우
#endif
			{
				for (int i = 0; i < 3; i++) // 사각형 범위 안에 터치한 점들 중에 원 안에 있는 점인지 판별한다.
				{
					C2 = ((point.x - t_2ndCircleTable[i].center_x) * (point.x - t_2ndCircleTable[i].center_x))
						+ ((point.y - t_2ndCircleTable[i].center_y) * (point.y - t_2ndCircleTable[i].center_y)); // C² = A² + B²
					if (C2 < (t_2ndCircleTable[i].radius * t_2ndCircleTable[i].radius)) // C²이 r²보다 작으면 원 안에 있다.
					{
						//SetDlgItemText(IDC_STATIC_VALUE, _T("i번 칸 터치"));
						idxSelect = i;
#if(CIRCLE_TEST!=1)
						display_text.Format(_T("idx = %d Inside"), idxSelect);
#endif
						is_in = TRUE;
						break;
					}
				}
			}
		}
		// 시간 측정

		//if (is_in != TRUE) // 터치가 원의 범위 안에 정확하게 없을 경우
		//{
		//	display_text.Format(_T("Outside"));
		//}
#if (CIRCLE_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("%dms") /*idxSelect*/, end_time - start_time);
#endif
		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	case eAlgorithmType_3rdRectangle:

#if (RECTANGLE_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{
			// i. 범위 사각형 알고리즘
			if ((point.x >= (t_3rdRectangleTable[0][0]).x) && (point.x < (t_3rdRectangleTable[2][1]).x)
				&& (point.y >= (t_3rdRectangleTable[0][0]).y) && (point.y < (t_3rdRectangleTable[0][2]).y))// 터치가 범위 안에 있을 경우
			{
#if (SEL_RECTANGLE_ALGORITHM==0)	// i-1. original 범위 사각형 알고리즘
				for (int i = 0; i < 3; i++)
				{
					if ((point.x >= (t_3rdRectangleTable[i][0]).x) && (point.x < (t_3rdRectangleTable[i][1]).x))
					{
						//SetDlgItemText(IDC_STATIC_VALUE, _T("i번 칸 터치"));
						idxSelect = i;
#if (RECTANGLE_TEST!=1)
						display_text.Format(_T("idx=%d Inside"), idxSelect);
#endif
						break;
					}
				}

#else	// ii. optimized 범위 사각형 알고리즘
				idxSelect = (point.x - t_3rdRectangleTable[0][0].x) / (t_3rdRectangleTable[1][0].x - t_3rdRectangleTable[0][0].x); // (최대 x좌표 - 현재 x좌표)/(사각형 한칸의 x좌표 범위)
#if (RECTANGLE_TEST!=1)
				display_text.Format(_T("idx=%d Inside"), idxSelect);
#endif
#endif
			}
			else// 터치가 범위 안에 없을 경우
			{
				display_text.Format(_T("Outside"));
			}
			// 범위 사각형 알고리즘 끝
		}
#if (RECTANGLE_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("idx : %d, %dms"), idxSelect, end_time - start_time);
#endif

		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;



	case eAlgorithmType_3rd6pPolygon:

#if 1
		is_in = FALSE; // 점이 다각형 안에 있는지?

		// int iCrosses = 0; // 교차 횟수 
#if (SEL_POLYGON_RANGE==1)
		if (((t_3rdPolygon6p1stTable[0][0].y <= point.y) && (t_3rdPolygon6p1stTable[2][4].y >= point.y))
			&& ((t_3rdPolygon6p1stTable[3][0].x <= point.x) && (t_3rdPolygon6p1stTable[1][1].x >= point.x)))
#endif
		{
			for (int n = 0; n < 5; n++) // 5개의 다각형이 있다.
			{
				iCrosses = 0;
				for (int i = 0; i < 6; i++) // 육각형이다.
				{
					j = (i + 1) % 6; //점이 선분의 y좌표 사이에 있다.

#if (SEL_POLYGON_ALGORITHM==2)
//    isLeft: >0 for P2  선분 왼쪽
//            =0 for P2  선분 위
//            <0 for P2  선분 오른쪽
					if (t_3rdPolygon6p1stTable[n][i].y <= point.y)
					{
						if (t_3rdPolygon6p1stTable[n][j].y > point.y)
						{
							if (isLeft(t_3rdPolygon6p1stTable[n][i], t_3rdPolygon6p1stTable[n][j], point) > 0)
							{
								iCrosses++;
							}
						}
					}
					else
					{
						if (t_3rdPolygon6p1stTable[n][j].y <= point.y)
						{
							if (isLeft(t_3rdPolygon6p1stTable[n][i], t_3rdPolygon6p1stTable[n][j], point) < 0)
							{
								iCrosses--;
							}
						}
					}
#endif

#if (SEL_POLYGON_ALGORITHM==0||SEL_POLYGON_ALGORITHM==1)
					// interSection는 점을 지나는 수평선과 선분의 교점 
					if ((t_3rdPolygon6p1stTable[n][i].y > point.y) != (t_3rdPolygon6p1stTable[n][j].y > point.y)) // 선분을 이루는 두 점의 y좌표가 수평선을 중간에 둔다.
#endif
					{
#if (SEL_POLYGON_ALGORITHM==0)
						interSection =
							(((float)(t_3rdPolygon6p1stTable[n][j].x - t_3rdPolygon6p1stTable[n][i].x) / (float)(t_3rdPolygon6p1stTable[n][j].y - t_3rdPolygon6p1stTable[n][i].y))
								* (float)(point.y - t_3rdPolygon6p1stTable[n][i].y)) // 기울기의 역수와 y좌표의 변화값을 곱하면 x좌표의 변화값이 나온다
							+ (float)t_3rdPolygon6p1stTable[n][i].x; //
						if (point.x < interSection) iCrosses++; // interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 
#elif (SEL_POLYGON_ALGORITHM==1)
						optInterSection =
							(t_3rdPolygon6p1stTable[n][j].x - t_3rdPolygon6p1stTable[n][i].x) * (point.y - t_3rdPolygon6p1stTable[n][i].y);

						presentX = (point.x - t_3rdPolygon6p1stTable[n][i].x) * (t_3rdPolygon6p1stTable[n][j].y - t_3rdPolygon6p1stTable[n][i].y);

						// 양수 음수 판별 최적화

						if ((t_3rdPolygon6p1stTable[n][j].y - t_3rdPolygon6p1stTable[n][i].y) < 0)
						{
							if (presentX > optInterSection)
							{
								iCrosses++;
							}
						}
						else
						{
							if (presentX < optInterSection)
							{
								iCrosses++;
							}// interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 
						}
#endif

					}
				}

				// 홀수면 내부, 짝수면 외부에 있음 
				if ((iCrosses & 0x01) == 1) // (iCrosses % 2) == 1
				{
					//bPointInPolygon = TRUE;
					is_in = TRUE;
					idxSelect = n;
#if (POLYGON_TEST!=1)
					display_text.Format(_T("idx=%d, cross=%d Inside"), idxSelect, iCrosses);
#endif
					break;
				}
			}
		}

		if (is_in == FALSE)
		{
			display_text.Format(_T("cross=%d Outside"), iCrosses);
		}
#endif

		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	case eAlgorithmType_3rd5pPolygon:
#if (POLYGON_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{

			is_in = FALSE; // 점이 다각형 안에 있는지?

		// int iCrosses = 0; // 교차 횟수 
#if (SEL_POLYGON_RANGE==1)
			if (((t_3rdPolygon6p2ndTable[0][1].y <= point.y) && (t_3rdPolygon6p2ndTable[1][3].y >= point.y))
				&& ((t_3rdPolygon6p2ndTable[0][0].x <= point.x) && (t_3rdPolygon6p2ndTable[2][3].x >= point.x)))
#endif
			{
				for (int n = 0; n < 3; n++) // 3개의 다각형이 있다.
				{
					iCrosses = 0;
					for (int i = 0; i < 6; i++) // 육각형이다.
					{
						j = (i + 1) % 6; //점이 선분의 y좌표 사이에 있다.

#if (SEL_POLYGON_ALGORITHM==2)
//    isLeft: >0 for P2  선분 왼쪽
//            =0 for P2  선분 위
//            <0 for P2  선분 오른쪽
						if (t_3rdPolygon6p2ndTable[n][i].y <= point.y)
						{
							if (t_3rdPolygon6p2ndTable[n][j].y > point.y)
							{
								if (isLeft(t_3rdPolygon6p2ndTable[n][i], t_3rdPolygon6p2ndTable[n][j], point) > 0)
								{
									iCrosses++;
								}
							}
						}
						else
						{
							if (t_3rdPolygon6p2ndTable[n][j].y <= point.y)
							{
								if (isLeft(t_3rdPolygon6p2ndTable[n][i], t_3rdPolygon6p2ndTable[n][j], point) < 0)
								{
									iCrosses--;
								}
							}
						}
#endif

						// interSection는 점을 지나는 수평선과 선분의 교점 
#if (SEL_POLYGON_ALGORITHM==0||SEL_POLYGON_ALGORITHM==1)
						if ((t_3rdPolygon6p2ndTable[n][i].y > point.y) != (t_3rdPolygon6p2ndTable[n][j].y > point.y)) // 선분을 이루는 두 점의 y좌표가 수평선을 중간에 둔다.
#endif
						{
#if (SEL_POLYGON_ALGORITHM==0)
							interSection =
								(((float)(t_3rdPolygon6p2ndTable[n][j].x - t_3rdPolygon6p2ndTable[n][i].x) / (float)(t_3rdPolygon6p2ndTable[n][j].y - t_3rdPolygon6p2ndTable[n][i].y))
									* (float)(point.y - t_3rdPolygon6p2ndTable[n][i].y)) // 기울기의 역수와 y좌표의 변화값을 곱하면 x좌표의 변화값이 나온다
								+ (float)t_3rdPolygon6p2ndTable[n][i].x; //
							if (point.x < interSection) iCrosses++; // interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 

#elif (SEL_POLYGON_ALGORITHM==1)
							optInterSection =
								(t_3rdPolygon6p2ndTable[n][j].x - t_3rdPolygon6p2ndTable[n][i].x) * (point.y - t_3rdPolygon6p2ndTable[n][i].y);

							presentX = (point.x - t_3rdPolygon6p2ndTable[n][i].x) * (t_3rdPolygon6p2ndTable[n][j].y - t_3rdPolygon6p2ndTable[n][i].y);

							// 양수 음수 판별 최적화

							if ((t_3rdPolygon6p2ndTable[n][j].y - t_3rdPolygon6p2ndTable[n][i].y) < 0)
							{
								if (presentX > optInterSection)
								{
									iCrosses++;
								}
							}
							else
							{
								if (presentX < optInterSection)
								{
									iCrosses++;
								}// interSection보다 x좌표가 왼쪽에 있으면 교점의 개수를 증가시킨다. 
							}
#endif
						}
					}

					// 홀수면 내부, 짝수면 외부에 있음 
					if ((iCrosses & 0x01) == 1) // (iCrosses % 2) == 1
					{
						//bPointInPolygon = TRUE;
						is_in = TRUE;
						idxSelect = n;
#if (POLYGON_TEST!=1)
						display_text.Format(_T("idx=%d,cross=%d Inside"), idxSelect, iCrosses);
#endif
						break;
					}
				}
			}


			if (is_in == FALSE)
			{
				display_text.Format(_T("cross=%d Outside"), iCrosses);
			}
		}
#if (POLYGON_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("idx = %d, %dms"), idxSelect, end_time - start_time);
#endif
		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	case eAlgorithmType_1rdCycleAlgorithm:

		float radian;
		int integer_radian;
		int degree;
		int areaSelect;
		float m;
		int M;
		int divisor; // 기울기 알고리즘에서 나눗셈 하지 않기 위함
		const int* t_SlopeTable;


#if (CYCLE_TEST==1)
		start_time = GetTickCount64();
		for (int test_count = 0; test_count < TEST_COUNT; test_count++)
#endif
		{
			C2 = ((point.x - t_1rdCycleAlgorithm[0].center_x) * (point.x - t_1rdCycleAlgorithm[0].center_x))
				+ ((point.y - t_1rdCycleAlgorithm[0].center_y) * (point.y - t_1rdCycleAlgorithm[0].center_y)); // C² = A² + B²


			if ((C2 <= (t_1rdCycleAlgorithm[0].radius * t_1rdCycleAlgorithm[0].radius))
				&& (C2 >= (t_1rdCycleAlgorithm[1].radius * t_1rdCycleAlgorithm[1].radius))) // r² < C² < R²이면 원 안에 있다.
			{
#if (SEL_CYCLE_ALGORITHM==0)
				//	각도 계산하는 초기의 알고리즘
				radian = (float)(atan2(point.y - t_1rdCycleAlgorithm[0].center_y, point.x - t_1rdCycleAlgorithm[0].center_x));
				degree = (int)(180 / PI * radian); // (180/PI)*라디안 = 각도

				if (degree >= 0)
				{
					areaSelect = degree / 10 + 9;
				}
				else if (degree > -90)
				{
					areaSelect = degree / 10 + 8;
				}
				else
				{
					areaSelect = degree / 10 + 44;
				}
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, %d°, idx : %d, (%d,%d)"), degree, areaSelect, point.x, point.y);
#endif

#elif (SEL_CYCLE_ALGORITHM==1)
#if 1
				//	라디안 계산하고 나눗셈 없앤 알고리즘
				radian = (float)(atan2(point.y - t_1rdCycleAlgorithm[0].center_y, point.x - t_1rdCycleAlgorithm[0].center_x));
				//	degree = (int)(180 / PI * radian); // (180/PI)*라디안 = 각도
				degree = 57.2957795f * radian;

				if (degree >= -90)
				{
					areaSelect = 0.1f * degree + 9;	// (180 / PI * radian) / 10 + 9
				}
				else
				{
					areaSelect = 0.1f * degree + 45; // (180 / PI * radian) / 10 + 44 
				}
#else
#endif
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, %d°, idx : %d, (%d,%d)"), degree, areaSelect, point.x, point.y);
#endif

#elif (SEL_CYCLE_ALGORITHM==2)
				// 직선의 기울기로 구성하는 알고리즘
				m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);

				if (point.x >= t_1rdCycleAlgorithm[0].center_x)
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						for (int i = 0; i < 9; i++)
						{
							if ((t_CycleSlopeTable[i + 1] <= m) && (t_CycleSlopeTable[i] >= m))
							{
								areaSelect = i;
								break;
							}
						}
					}
					else
					{
						//4사분면
						for (int i = 0; i < 9; i++)
						{
							if ((-t_CycleSlopeTable[9 - i] >= m) && (-t_CycleSlopeTable[8 - i] <= m))
							{
								areaSelect = i + 9;
								break;
							}
						}
					}
				}
				else
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						for (int i = 0; i < 9; i++)
						{
							if ((-t_CycleSlopeTable[9 - i] >= m) && (-t_CycleSlopeTable[8 - i] <= m))
							{
								areaSelect = i + 27;
								break;
							}
						}
					}
					else
					{
						//3사분면
						for (int i = 0; i < 9; i++)
						{
							if ((t_CycleSlopeTable[i + 1] <= m) && (t_CycleSlopeTable[i] >= m))
							{
								areaSelect = i + 18;
								break;
							}
						}
					}
				}
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, m : %f, idx : %d, (%d,%d)"), m, areaSelect, point.x, point.y);
#endif

#elif (SEL_CYCLE_ALGORITHM==3)
				// 직선의 기울기 알고리즘 최적화버전
				M = t_1rdCycleAlgorithm[0].center_y - point.y; // M은 기울기 m에서 나눗셈을 제거한 값
				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);

				divisor = point.x - t_1rdCycleAlgorithm[0].center_x; // divisor는 기존의 기울기 구하는 나눗셈의 제수

				if (divisor >= 0) // (point.x - t_1rdCycleAlgorithm[0].center_x)가 양수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						for (int i = 0; i < 9; i++)
						{
							if (t_CycleSlopeTable[i + 1] * divisor <= M)
							{
								areaSelect = i;
								break;
							}
						}
					}
					else
					{
						//4사분면
						for (int i = 0; i < 9; i++)
						{
							if (-t_CycleSlopeTable[8 - i] * divisor <= M)
							{
								areaSelect = i + 9;
								break;
							}
						}
					}
				}
				else // (point.x - t_1rdCycleAlgorithm[0].center_x)가 음수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						for (int i = 0; i < 9; i++)
						{
							if (-t_CycleSlopeTable[8 - i] * divisor >= M)
							{
								areaSelect = i + 27;
								break;
							}
						}
					}
					else
					{
						//3사분면
						for (int i = 0; i < 9; i++)
						{
							if (t_CycleSlopeTable[i + 1] * divisor >= M)
							{
								areaSelect = i + 18;
								break;
							}
						}
					}
				}
				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);
				// m은 직선의 기울기 확인용이고 나중에 주석 처리해야한다.
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, M : %d, idx : %d, (%d,%d)"), M, areaSelect, point.x, point.y);
#endif

#elif (SEL_CYCLE_ALGORITHM==4)
#if 1
				// 직선의 기울기 알고리즘 최적화 + 정수화 100배 테이블
				M = (t_1rdCycleAlgorithm[0].center_y - point.y) * 100; // M은 (기울기 m에서 나눗셈을 제거한 값 M) * 100
				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);
				t_SlopeTable = t_IntegerSlopeTable100;
#else
				// 직선의 기울기 알고리즘 최적화 + 정수화 100배 테이블
				M = (t_1rdCycleAlgorithm[0].center_y - point.y) * 1000; // M은 (기울기 m에서 나눗셈을 제거한 값 M) * 1000
				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);
				t_SlopeTable = t_IntegerSlopeTable1000;
#endif
				divisor = point.x - t_1rdCycleAlgorithm[0].center_x; // divisor는 기존의 기울기 구하는 나눗셈의 제수

				if (divisor >= 0) // (point.x - t_1rdCycleAlgorithm[0].center_x)가 양수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						for (int i = 0; i < 9; i++)
						{
							if (t_SlopeTable[i + 1] * divisor <= M)
							{
								areaSelect = i;
								break;
							}
						}
					}
					else
					{
						//4사분면
						for (int i = 0; i < 9; i++)
						{
							if (-t_SlopeTable[8 - i] * divisor <= M)
							{
								areaSelect = i + 9;
								break;
							}
						}
					}
				}
				else // (point.x - t_1rdCycleAlgorithm[0].center_x)가 음수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						for (int i = 0; i < 9; i++)
						{
							if (-t_SlopeTable[8 - i] * divisor >= M)
							{
								areaSelect = i + 27;
								break;
							}
						}
					}
					else
					{
						//3사분면
						for (int i = 0; i < 9; i++)
						{
							if (t_SlopeTable[i + 1] * divisor >= M)
							{
								areaSelect = i + 18;
								break;
							}
						}
					}
				}

				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);
				// m은 직선의 기울기 확인용이고 나중에 주석 처리해야한다.
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, M : %d, idx : %d, (%d,%d)"), M, areaSelect, point.x, point.y);
#endif

#elif (SEL_CYCLE_ALGORITHM==5)
				// 최종 최적화버전, for문을 개선하였다.
				M = (t_1rdCycleAlgorithm[0].center_y - point.y) * 100; // M은 (기울기 m에서 나눗셈을 제거한 값 M) * 100

				divisor = point.x - t_1rdCycleAlgorithm[0].center_x; // divisor는 기존의 기울기 구하는 나눗셈의 제수

				if (divisor >= 0) // (point.x - t_1rdCycleAlgorithm[0].center_x)가 양수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						for (int i = 0; i < 5; i++)
						{
							if (t_IntegerSlopeTable100[i + 1] * divisor <= M)
							{
								areaSelect = i;
								break;
							}
							else if (t_IntegerSlopeTable100[8 - i] * divisor >= M) 
							{
								areaSelect = 8 - i;
								break;
							}
						}
					}
					else
					{
						//4사분면
						for (int i = 0; i < 5; i++)
						{
							if (-t_IntegerSlopeTable100[8 - i] * divisor <= M)
							{
								areaSelect = i + 9;
								break;
							}
							else if (-t_IntegerSlopeTable100[i + 1] * divisor >= M)
							{
								areaSelect = 17 - i;
								break;
							}
						}
					}
				}
				else // (point.x - t_1rdCycleAlgorithm[0].center_x)가 음수
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						for (int i = 0; i < 5; i++)
						{
							if (-t_IntegerSlopeTable100[8 - i] * divisor >= M)
							{
								areaSelect = i + 27;
								break;
							}
							else if (-t_IntegerSlopeTable100[i + 1] * divisor <= M)
							{
								areaSelect = 35 - i;
								break;
							}
						}
					}
					else
					{
						//3사분면
						for (int i = 0; i < 5; i++)
						{
							if (t_IntegerSlopeTable100[i + 1] * divisor >= M)
							{
								areaSelect = i + 18;
								break;
							}
							else if (t_IntegerSlopeTable100[8 - i] * divisor <= M)
							{
								areaSelect = 26 - i;
								break;
							}
						}
					}
				}

				//m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);
				// m은 직선의 기울기 확인용이고 나중에 주석 처리해야한다.
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, M : %d, idx : %d, (%d,%d)"), M, areaSelect, point.x, point.y);
#endif
#elif (SEL_CYCLE_ALGORITHM==6)
// 이진 탐색 기법 사용
				m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);


				M = m * 100;


				if (point.x > t_1rdCycleAlgorithm[0].center_x)
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						areaSelect = binsearch(M, 0, 9);
					}
					else
					{
						//4사분면
						areaSelect = minus_binsearch(-M, 0, 9) + 9;
					}
				}
				else
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						areaSelect = minus_binsearch(-M, 0, 9) + 27;
					}
					else
					{
						//3사분면
						areaSelect = binsearch(M, 0, 9) + 18;
					}
				}
#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, M : %d, idx : %d, (%d,%d)"), M, areaSelect, point.x, point.y);
#endif
#elif (SEL_CYCLE_ALGORITHM==7)
				/*if ((point.x >= t_1rdCycleAlgorithm[0].center_x- t_1rdCycleAlgorithm[0].radius) 
					&& (point.x <= t_1rdCycleAlgorithm[0].center_x + t_1rdCycleAlgorithm[0].radius) 
					&& (point.y >= t_1rdCycleAlgorithm[0].center_y - t_1rdCycleAlgorithm[0].radius) 
					&& (point.y <= t_1rdCycleAlgorithm[0].center_y - t_1rdCycleAlgorithm[0].radius))
				*/
				areaSelect = t_BinaryResultTable[point.x - 320][point.y - 158];
				if (areaSelect == -1)
				{
#if (CYCLE_TEST!=1)
					display_text.Format(_T("Outside"));
#endif
				}
				else
				{
#if (CYCLE_TEST!=1)
					display_text.Format(_T("Inside, init time : %dms, idx : %d, (%d,%d)"), init_time, areaSelect, point.x, point.y);
#endif
				}
				

#elif (SEL_CYCLE_ALGORITHM==8)
				if (point.x == t_1rdCycleAlgorithm[0].center_x)
				{
					point.x = point.x - 1;
				}
				m = (float)(t_1rdCycleAlgorithm[0].center_y - point.y) / (float)(point.x - t_1rdCycleAlgorithm[0].center_x);


				M = m * 100;

				if (point.x >= t_1rdCycleAlgorithm[0].center_x)
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//1사분면, 그냥 그대로
						areaSelect = bintree_reverse_search(M);
					}
					else
					{
						//4사분면
						areaSelect = bintree_search(-M) + 9;
					}
				}
				else
				{
					if (point.y <= t_1rdCycleAlgorithm[0].center_y)
					{
						//2사분면
						areaSelect = bintree_search(-M) + 27;
					}
					else
					{
						//3사분면
						areaSelect = bintree_reverse_search(M) + 18;
					}
				}

#if (CYCLE_TEST!=1)
				display_text.Format(_T("Inside, idx : %d, M : %d, (%d,%d)"),areaSelect, M, point.x, point.y);
#endif
				

#endif
			}
			else
			{
				display_text.Format(_T("Outside"));
			}
		}
#if (CYCLE_TEST==1)
		end_time = GetTickCount64();
		display_text.Format(_T("idx : %d, %dms"), areaSelect, end_time - start_time);
#endif
		
		SetDlgItemText(IDC_STATIC_VALUE, display_text);
		break;


	default: break;
	}
}

int minus_binsearch(int searchnum, int left, int right) // t_SortedIntTable100 안에서 도는 이진 검색 함수
{
	int middle;		// left = 0, right = n-1 로 전달
	while (left <= right)
	{
		middle = (left + right) / 2;
		switch (minus_compare(middle, searchnum))
		{
		case  -1:
			right = middle - 1;
			break;
		case   0:
			return middle;
		case   1:
			left = middle + 1;
		}
	}
	return 8; // INT_MIN 인덱스 처리
}

int binsearch(int searchnum, int left, int right) // t_SortedIntTable100 안에서 도는 이진 검색 함수
{
	int middle;		// left = 0, right = n-1 로 전달
	while (left <= right)
	{
		middle = (left + right) / 2;
		switch (compare(middle, searchnum))
		{
		case  -1:
			right = middle - 1;
			break;
		case   0:
			return middle;
		case   1:
			left = middle + 1;
		}
	}
	return -1;
}

inline int minus_compare(int middle, int searchnum)
{
	return (searchnum < t_SortedIntegerSlopeTable100[middle]) ? -1 :
		((t_SortedIntegerSlopeTable100[middle + 1] >= searchnum) && (searchnum >= t_SortedIntegerSlopeTable100[middle])) ? 0 : 1;
}

inline int compare(int middle, int searchnum)
{
	return (searchnum > t_IntegerSlopeTable100[middle]) ? -1 : 
		((t_IntegerSlopeTable100[middle + 1] <= searchnum) && (searchnum <= t_IntegerSlopeTable100[middle])) ? 0 : 1;
}

inline int bintree_compare(int middle, int searchnum)
{
	return (searchnum < t_SortedIntegerSlopeTable100[middle]) ? -1 :
		((t_SortedIntegerSlopeTable100[middle] <= searchnum) && (searchnum <= t_SortedIntegerSlopeTable100[middle + 1])) ? 0 : 1;
}


inline int bintree_reverse_compare(int middle, int searchnum)
{
	return (searchnum > t_IntegerSlopeTable100[middle]) ? -1 :
		((t_IntegerSlopeTable100[middle] >= searchnum) && (searchnum >= t_IntegerSlopeTable100[middle + 1])) ? 0 : 1;
}

int bintree_search(int M)
{
	node* temp = slopeTree;
	while (1)
	{
		switch (bintree_compare(temp->data, M))
		{
		case  -1:
			temp = temp->left;
			//right = middle - 1;
			break;
		case   0:
			return temp->data;
		case   1:
			temp = temp->right;
			//left = middle + 1;
		}
	}
}

int bintree_reverse_search(int M)
{
	node* temp = slopeTree;
	while (1)
	{
		switch (bintree_reverse_compare(temp->data, M))
		{
		case  -1:
			temp = temp->left;
			//right = middle - 1;
			break;
		case   0:
			return temp->data;
		case   1:
			temp = temp->right;
			//left = middle + 1;
		}
	}
}