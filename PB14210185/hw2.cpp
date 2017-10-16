#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//#define IMG_SHOW_WZG
#define MY_OK 1
#define MY_FAIL -1

int ustc_Find_Circles_By_Difference(Mat colorImg, int min_radius, int max_radius, int min_center_dist, int min_radius_dist, int max_circle_diff, int* x, int* y, int* radius, int* circle_cnt, int max_circle)
{
	if (NULL == colorImg.data)
	{
		cout << "image is NULL." << endl;
		return MY_FAIL;
	}
	if (colorImg.channels() != 3)
	{
		cout << "not a rgb_image." << endl;
		return MY_FAIL;
	}
	if (min_radius >= max_radius || min_radius <= 5)
	{
		cout << "wrong radius range." << endl;
		return MY_FAIL;
	}

	Mat RGBImg[3];
	split(colorImg, RGBImg);

	Mat R_canny, G_canny, B_canny;
	Canny(RGBImg[0], R_canny, 140, 420);
	Canny(RGBImg[1], G_canny, 140, 420);
	Canny(RGBImg[2], B_canny, 140, 420);
	uchar* ptr_R = R_canny.data;
	uchar* ptr_G = G_canny.data;
	uchar* ptr_B = B_canny.data;
#ifdef IMG_SHOW_WZG
	imshow("Img", colorImg);
	imshow("R_Img", RGBImg[0]);
	imshow("G_Img", RGBImg[1]);
	imshow("B_Img", RGBImg[2]);
	imshow("R_Canny", R_canny);
	imshow("G_Canny", G_canny);
	imshow("B_Canny", B_canny);
	waitKey();
#endif

	float Sin[360];
	float Cos[360];
	Sin[0] = 0; Cos[0] = 1; Sin[1] = 0.0174524; Cos[1] = 0.999848; Sin[2] = 0.0348995; Cos[2] = 0.999391; Sin[3] = 0.052336; Cos[3] = 0.99863; Sin[4] = 0.0697565; Cos[4] = 0.997564; Sin[5] = 0.0871557; Cos[5] = 0.996195; Sin[6] = 0.104528; Cos[6] = 0.994522; Sin[7] = 0.121869; Cos[7] = 0.992546; Sin[8] = 0.139173; Cos[8] = 0.990268; Sin[9] = 0.156434; Cos[9] = 0.987688; Sin[10] = 0.173648; Cos[10] = 0.984808; Sin[11] = 0.190809; Cos[11] = 0.981627; Sin[12] = 0.207912; Cos[12] = 0.978148; Sin[13] = 0.224951; Cos[13] = 0.97437; Sin[14] = 0.241922; Cos[14] = 0.970296; Sin[15] = 0.258819; Cos[15] = 0.965926; Sin[16] = 0.275637; Cos[16] = 0.961262; Sin[17] = 0.292372; Cos[17] = 0.956305; Sin[18] = 0.309017; Cos[18] = 0.951057; Sin[19] = 0.325568; Cos[19] = 0.945519; Sin[20] = 0.34202; Cos[20] = 0.939693; Sin[21] = 0.358368; Cos[21] = 0.93358; Sin[22] = 0.374607; Cos[22] = 0.927184; Sin[23] = 0.390731; Cos[23] = 0.920505; Sin[24] = 0.406737; Cos[24] = 0.913545; Sin[25] = 0.422618; Cos[25] = 0.906308; Sin[26] = 0.438371; Cos[26] = 0.898794; Sin[27] = 0.45399; Cos[27] = 0.891007; Sin[28] = 0.469472; Cos[28] = 0.882948; Sin[29] = 0.48481; Cos[29] = 0.87462; Sin[30] = 0.5; Cos[30] = 0.866025; Sin[31] = 0.515038; Cos[31] = 0.857167; Sin[32] = 0.529919; Cos[32] = 0.848048; Sin[33] = 0.544639; Cos[33] = 0.838671; Sin[34] = 0.559193; Cos[34] = 0.829038; Sin[35] = 0.573576; Cos[35] = 0.819152; Sin[36] = 0.587785; Cos[36] = 0.809017; Sin[37] = 0.601815; Cos[37] = 0.798635; Sin[38] = 0.615662; Cos[38] = 0.788011; Sin[39] = 0.62932; Cos[39] = 0.777146; Sin[40] = 0.642788; Cos[40] = 0.766044; Sin[41] = 0.656059; Cos[41] = 0.75471; Sin[42] = 0.669131; Cos[42] = 0.743145; Sin[43] = 0.681998; Cos[43] = 0.731354; Sin[44] = 0.694658; Cos[44] = 0.71934; Sin[45] = 0.707107; Cos[45] = 0.707107; Sin[46] = 0.71934; Cos[46] = 0.694658; Sin[47] = 0.731354; Cos[47] = 0.681998; Sin[48] = 0.743145; Cos[48] = 0.669131; Sin[49] = 0.75471; Cos[49] = 0.656059; Sin[50] = 0.766044; Cos[50] = 0.642788; Sin[51] = 0.777146; Cos[51] = 0.62932; Sin[52] = 0.788011; Cos[52] = 0.615662; Sin[53] = 0.798635; Cos[53] = 0.601815; Sin[54] = 0.809017; Cos[54] = 0.587785; Sin[55] = 0.819152; Cos[55] = 0.573576; Sin[56] = 0.829038; Cos[56] = 0.559193; Sin[57] = 0.838671; Cos[57] = 0.544639; Sin[58] = 0.848048; Cos[58] = 0.529919; Sin[59] = 0.857167; Cos[59] = 0.515038; Sin[60] = 0.866025; Cos[60] = 0.5; Sin[61] = 0.87462; Cos[61] = 0.48481; Sin[62] = 0.882948; Cos[62] = 0.469472; Sin[63] = 0.891007; Cos[63] = 0.45399; Sin[64] = 0.898794; Cos[64] = 0.438371; Sin[65] = 0.906308; Cos[65] = 0.422618; Sin[66] = 0.913545; Cos[66] = 0.406737; Sin[67] = 0.920505; Cos[67] = 0.390731; Sin[68] = 0.927184; Cos[68] = 0.374607; Sin[69] = 0.93358; Cos[69] = 0.358368; Sin[70] = 0.939693; Cos[70] = 0.34202; Sin[71] = 0.945519; Cos[71] = 0.325568; Sin[72] = 0.951057; Cos[72] = 0.309017; Sin[73] = 0.956305; Cos[73] = 0.292372; Sin[74] = 0.961262; Cos[74] = 0.275637; Sin[75] = 0.965926; Cos[75] = 0.258819; Sin[76] = 0.970296; Cos[76] = 0.241922; Sin[77] = 0.97437; Cos[77] = 0.224951; Sin[78] = 0.978148; Cos[78] = 0.207912; Sin[79] = 0.981627; Cos[79] = 0.190809; Sin[80] = 0.984808; Cos[80] = 0.173648; Sin[81] = 0.987688; Cos[81] = 0.156434; Sin[82] = 0.990268; Cos[82] = 0.139173; Sin[83] = 0.992546; Cos[83] = 0.121869; Sin[84] = 0.994522; Cos[84] = 0.104528; Sin[85] = 0.996195; Cos[85] = 0.0871557; Sin[86] = 0.997564; Cos[86] = 0.0697565; Sin[87] = 0.99863; Cos[87] = 0.052336; Sin[88] = 0.999391; Cos[88] = 0.0348995; Sin[89] = 0.999848; Cos[89] = 0.0174524; Sin[90] = 1; Cos[90] = 6.12323e-017; Sin[91] = 0.999848; Cos[91] = -0.0174524; Sin[92] = 0.999391; Cos[92] = -0.0348995; Sin[93] = 0.99863; Cos[93] = -0.052336; Sin[94] = 0.997564; Cos[94] = -0.0697565; Sin[95] = 0.996195; Cos[95] = -0.0871557; Sin[96] = 0.994522; Cos[96] = -0.104528; Sin[97] = 0.992546; Cos[97] = -0.121869; Sin[98] = 0.990268; Cos[98] = -0.139173; Sin[99] = 0.987688; Cos[99] = -0.156434; Sin[100] = 0.984808; Cos[100] = -0.173648; Sin[101] = 0.981627; Cos[101] = -0.190809; Sin[102] = 0.978148; Cos[102] = -0.207912; Sin[103] = 0.97437; Cos[103] = -0.224951; Sin[104] = 0.970296; Cos[104] = -0.241922; Sin[105] = 0.965926; Cos[105] = -0.258819; Sin[106] = 0.961262; Cos[106] = -0.275637; Sin[107] = 0.956305; Cos[107] = -0.292372; Sin[108] = 0.951057; Cos[108] = -0.309017; Sin[109] = 0.945519; Cos[109] = -0.325568; Sin[110] = 0.939693; Cos[110] = -0.34202; Sin[111] = 0.93358; Cos[111] = -0.358368; Sin[112] = 0.927184; Cos[112] = -0.374607; Sin[113] = 0.920505; Cos[113] = -0.390731; Sin[114] = 0.913545; Cos[114] = -0.406737; Sin[115] = 0.906308; Cos[115] = -0.422618; Sin[116] = 0.898794; Cos[116] = -0.438371; Sin[117] = 0.891007; Cos[117] = -0.45399; Sin[118] = 0.882948; Cos[118] = -0.469472; Sin[119] = 0.87462; Cos[119] = -0.48481; Sin[120] = 0.866025; Cos[120] = -0.5; Sin[121] = 0.857167; Cos[121] = -0.515038; Sin[122] = 0.848048; Cos[122] = -0.529919; Sin[123] = 0.838671; Cos[123] = -0.544639; Sin[124] = 0.829038; Cos[124] = -0.559193; Sin[125] = 0.819152; Cos[125] = -0.573576; Sin[126] = 0.809017; Cos[126] = -0.587785; Sin[127] = 0.798635; Cos[127] = -0.601815; Sin[128] = 0.788011; Cos[128] = -0.615662; Sin[129] = 0.777146; Cos[129] = -0.62932; Sin[130] = 0.766044; Cos[130] = -0.642788; Sin[131] = 0.75471; Cos[131] = -0.656059; Sin[132] = 0.743145; Cos[132] = -0.669131; Sin[133] = 0.731354; Cos[133] = -0.681998; Sin[134] = 0.71934; Cos[134] = -0.694658; Sin[135] = 0.707107; Cos[135] = -0.707107; Sin[136] = 0.694658; Cos[136] = -0.71934; Sin[137] = 0.681998; Cos[137] = -0.731354; Sin[138] = 0.669131; Cos[138] = -0.743145; Sin[139] = 0.656059; Cos[139] = -0.75471; Sin[140] = 0.642788; Cos[140] = -0.766044; Sin[141] = 0.62932; Cos[141] = -0.777146; Sin[142] = 0.615662; Cos[142] = -0.788011; Sin[143] = 0.601815; Cos[143] = -0.798635; Sin[144] = 0.587785; Cos[144] = -0.809017; Sin[145] = 0.573576; Cos[145] = -0.819152; Sin[146] = 0.559193; Cos[146] = -0.829038; Sin[147] = 0.544639; Cos[147] = -0.838671; Sin[148] = 0.529919; Cos[148] = -0.848048; Sin[149] = 0.515038; Cos[149] = -0.857167; Sin[150] = 0.5; Cos[150] = -0.866025; Sin[151] = 0.48481; Cos[151] = -0.87462; Sin[152] = 0.469472; Cos[152] = -0.882948; Sin[153] = 0.45399; Cos[153] = -0.891007; Sin[154] = 0.438371; Cos[154] = -0.898794; Sin[155] = 0.422618; Cos[155] = -0.906308; Sin[156] = 0.406737; Cos[156] = -0.913545; Sin[157] = 0.390731; Cos[157] = -0.920505; Sin[158] = 0.374607; Cos[158] = -0.927184; Sin[159] = 0.358368; Cos[159] = -0.93358; Sin[160] = 0.34202; Cos[160] = -0.939693; Sin[161] = 0.325568; Cos[161] = -0.945519; Sin[162] = 0.309017; Cos[162] = -0.951057; Sin[163] = 0.292372; Cos[163] = -0.956305; Sin[164] = 0.275637; Cos[164] = -0.961262; Sin[165] = 0.258819; Cos[165] = -0.965926; Sin[166] = 0.241922; Cos[166] = -0.970296; Sin[167] = 0.224951; Cos[167] = -0.97437; Sin[168] = 0.207912; Cos[168] = -0.978148; Sin[169] = 0.190809; Cos[169] = -0.981627; Sin[170] = 0.173648; Cos[170] = -0.984808; Sin[171] = 0.156434; Cos[171] = -0.987688; Sin[172] = 0.139173; Cos[172] = -0.990268; Sin[173] = 0.121869; Cos[173] = -0.992546; Sin[174] = 0.104528; Cos[174] = -0.994522; Sin[175] = 0.0871557; Cos[175] = -0.996195; Sin[176] = 0.0697565; Cos[176] = -0.997564; Sin[177] = 0.052336; Cos[177] = -0.99863; Sin[178] = 0.0348995; Cos[178] = -0.999391; Sin[179] = 0.0174524; Cos[179] = -0.999848; Sin[180] = 1.22465e-016; Cos[180] = -1; Sin[181] = -0.0174524; Cos[181] = -0.999848; Sin[182] = -0.0348995; Cos[182] = -0.999391; Sin[183] = -0.052336; Cos[183] = -0.99863; Sin[184] = -0.0697565; Cos[184] = -0.997564; Sin[185] = -0.0871557; Cos[185] = -0.996195; Sin[186] = -0.104528; Cos[186] = -0.994522; Sin[187] = -0.121869; Cos[187] = -0.992546; Sin[188] = -0.139173; Cos[188] = -0.990268; Sin[189] = -0.156434; Cos[189] = -0.987688; Sin[190] = -0.173648; Cos[190] = -0.984808; Sin[191] = -0.190809; Cos[191] = -0.981627; Sin[192] = -0.207912; Cos[192] = -0.978148; Sin[193] = -0.224951; Cos[193] = -0.97437; Sin[194] = -0.241922; Cos[194] = -0.970296; Sin[195] = -0.258819; Cos[195] = -0.965926; Sin[196] = -0.275637; Cos[196] = -0.961262; Sin[197] = -0.292372; Cos[197] = -0.956305; Sin[198] = -0.309017; Cos[198] = -0.951057; Sin[199] = -0.325568; Cos[199] = -0.945519; Sin[200] = -0.34202; Cos[200] = -0.939693; Sin[201] = -0.358368; Cos[201] = -0.93358; Sin[202] = -0.374607; Cos[202] = -0.927184; Sin[203] = -0.390731; Cos[203] = -0.920505; Sin[204] = -0.406737; Cos[204] = -0.913545; Sin[205] = -0.422618; Cos[205] = -0.906308; Sin[206] = -0.438371; Cos[206] = -0.898794; Sin[207] = -0.45399; Cos[207] = -0.891007; Sin[208] = -0.469472; Cos[208] = -0.882948; Sin[209] = -0.48481; Cos[209] = -0.87462; Sin[210] = -0.5; Cos[210] = -0.866025; Sin[211] = -0.515038; Cos[211] = -0.857167; Sin[212] = -0.529919; Cos[212] = -0.848048; Sin[213] = -0.544639; Cos[213] = -0.838671; Sin[214] = -0.559193; Cos[214] = -0.829038; Sin[215] = -0.573576; Cos[215] = -0.819152; Sin[216] = -0.587785; Cos[216] = -0.809017; Sin[217] = -0.601815; Cos[217] = -0.798635; Sin[218] = -0.615662; Cos[218] = -0.788011; Sin[219] = -0.62932; Cos[219] = -0.777146; Sin[220] = -0.642788; Cos[220] = -0.766044; Sin[221] = -0.656059; Cos[221] = -0.75471; Sin[222] = -0.669131; Cos[222] = -0.743145; Sin[223] = -0.681998; Cos[223] = -0.731354; Sin[224] = -0.694658; Cos[224] = -0.71934; Sin[225] = -0.707107; Cos[225] = -0.707107; Sin[226] = -0.71934; Cos[226] = -0.694658; Sin[227] = -0.731354; Cos[227] = -0.681998; Sin[228] = -0.743145; Cos[228] = -0.669131; Sin[229] = -0.75471; Cos[229] = -0.656059; Sin[230] = -0.766044; Cos[230] = -0.642788; Sin[231] = -0.777146; Cos[231] = -0.62932; Sin[232] = -0.788011; Cos[232] = -0.615662; Sin[233] = -0.798635; Cos[233] = -0.601815; Sin[234] = -0.809017; Cos[234] = -0.587785; Sin[235] = -0.819152; Cos[235] = -0.573576; Sin[236] = -0.829038; Cos[236] = -0.559193; Sin[237] = -0.838671; Cos[237] = -0.544639; Sin[238] = -0.848048; Cos[238] = -0.529919; Sin[239] = -0.857167; Cos[239] = -0.515038; Sin[240] = -0.866025; Cos[240] = -0.5; Sin[241] = -0.87462; Cos[241] = -0.48481; Sin[242] = -0.882948; Cos[242] = -0.469472; Sin[243] = -0.891007; Cos[243] = -0.45399; Sin[244] = -0.898794; Cos[244] = -0.438371; Sin[245] = -0.906308; Cos[245] = -0.422618; Sin[246] = -0.913545; Cos[246] = -0.406737; Sin[247] = -0.920505; Cos[247] = -0.390731; Sin[248] = -0.927184; Cos[248] = -0.374607; Sin[249] = -0.93358; Cos[249] = -0.358368; Sin[250] = -0.939693; Cos[250] = -0.34202; Sin[251] = -0.945519; Cos[251] = -0.325568; Sin[252] = -0.951057; Cos[252] = -0.309017; Sin[253] = -0.956305; Cos[253] = -0.292372; Sin[254] = -0.961262; Cos[254] = -0.275637; Sin[255] = -0.965926; Cos[255] = -0.258819; Sin[256] = -0.970296; Cos[256] = -0.241922; Sin[257] = -0.97437; Cos[257] = -0.224951; Sin[258] = -0.978148; Cos[258] = -0.207912; Sin[259] = -0.981627; Cos[259] = -0.190809; Sin[260] = -0.984808; Cos[260] = -0.173648; Sin[261] = -0.987688; Cos[261] = -0.156434; Sin[262] = -0.990268; Cos[262] = -0.139173; Sin[263] = -0.992546; Cos[263] = -0.121869; Sin[264] = -0.994522; Cos[264] = -0.104528; Sin[265] = -0.996195; Cos[265] = -0.0871557; Sin[266] = -0.997564; Cos[266] = -0.0697565; Sin[267] = -0.99863; Cos[267] = -0.052336; Sin[268] = -0.999391; Cos[268] = -0.0348995; Sin[269] = -0.999848; Cos[269] = -0.0174524; Sin[270] = -1; Cos[270] = -1.83697e-016; Sin[271] = -0.999848; Cos[271] = 0.0174524; Sin[272] = -0.999391; Cos[272] = 0.0348995; Sin[273] = -0.99863; Cos[273] = 0.052336; Sin[274] = -0.997564; Cos[274] = 0.0697565; Sin[275] = -0.996195; Cos[275] = 0.0871557; Sin[276] = -0.994522; Cos[276] = 0.104528; Sin[277] = -0.992546; Cos[277] = 0.121869; Sin[278] = -0.990268; Cos[278] = 0.139173; Sin[279] = -0.987688; Cos[279] = 0.156434; Sin[280] = -0.984808; Cos[280] = 0.173648; Sin[281] = -0.981627; Cos[281] = 0.190809; Sin[282] = -0.978148; Cos[282] = 0.207912; Sin[283] = -0.97437; Cos[283] = 0.224951; Sin[284] = -0.970296; Cos[284] = 0.241922; Sin[285] = -0.965926; Cos[285] = 0.258819; Sin[286] = -0.961262; Cos[286] = 0.275637; Sin[287] = -0.956305; Cos[287] = 0.292372; Sin[288] = -0.951057; Cos[288] = 0.309017; Sin[289] = -0.945519; Cos[289] = 0.325568; Sin[290] = -0.939693; Cos[290] = 0.34202; Sin[291] = -0.93358; Cos[291] = 0.358368; Sin[292] = -0.927184; Cos[292] = 0.374607; Sin[293] = -0.920505; Cos[293] = 0.390731; Sin[294] = -0.913545; Cos[294] = 0.406737; Sin[295] = -0.906308; Cos[295] = 0.422618; Sin[296] = -0.898794; Cos[296] = 0.438371; Sin[297] = -0.891007; Cos[297] = 0.45399; Sin[298] = -0.882948; Cos[298] = 0.469472; Sin[299] = -0.87462; Cos[299] = 0.48481; Sin[300] = -0.866025; Cos[300] = 0.5; Sin[301] = -0.857167; Cos[301] = 0.515038; Sin[302] = -0.848048; Cos[302] = 0.529919; Sin[303] = -0.838671; Cos[303] = 0.544639; Sin[304] = -0.829038; Cos[304] = 0.559193; Sin[305] = -0.819152; Cos[305] = 0.573576; Sin[306] = -0.809017; Cos[306] = 0.587785; Sin[307] = -0.798635; Cos[307] = 0.601815; Sin[308] = -0.788011; Cos[308] = 0.615662; Sin[309] = -0.777146; Cos[309] = 0.62932; Sin[310] = -0.766044; Cos[310] = 0.642788; Sin[311] = -0.75471; Cos[311] = 0.656059; Sin[312] = -0.743145; Cos[312] = 0.669131; Sin[313] = -0.731354; Cos[313] = 0.681998; Sin[314] = -0.71934; Cos[314] = 0.694658; Sin[315] = -0.707107; Cos[315] = 0.707107; Sin[316] = -0.694658; Cos[316] = 0.71934; Sin[317] = -0.681998; Cos[317] = 0.731354; Sin[318] = -0.669131; Cos[318] = 0.743145; Sin[319] = -0.656059; Cos[319] = 0.75471; Sin[320] = -0.642788; Cos[320] = 0.766044; Sin[321] = -0.62932; Cos[321] = 0.777146; Sin[322] = -0.615662; Cos[322] = 0.788011; Sin[323] = -0.601815; Cos[323] = 0.798635; Sin[324] = -0.587785; Cos[324] = 0.809017; Sin[325] = -0.573576; Cos[325] = 0.819152; Sin[326] = -0.559193; Cos[326] = 0.829038; Sin[327] = -0.544639; Cos[327] = 0.838671; Sin[328] = -0.529919; Cos[328] = 0.848048; Sin[329] = -0.515038; Cos[329] = 0.857167; Sin[330] = -0.5; Cos[330] = 0.866025; Sin[331] = -0.48481; Cos[331] = 0.87462; Sin[332] = -0.469472; Cos[332] = 0.882948; Sin[333] = -0.45399; Cos[333] = 0.891007; Sin[334] = -0.438371; Cos[334] = 0.898794; Sin[335] = -0.422618; Cos[335] = 0.906308; Sin[336] = -0.406737; Cos[336] = 0.913545; Sin[337] = -0.390731; Cos[337] = 0.920505; Sin[338] = -0.374607; Cos[338] = 0.927184; Sin[339] = -0.358368; Cos[339] = 0.93358; Sin[340] = -0.34202; Cos[340] = 0.939693; Sin[341] = -0.325568; Cos[341] = 0.945519; Sin[342] = -0.309017; Cos[342] = 0.951057; Sin[343] = -0.292372; Cos[343] = 0.956305; Sin[344] = -0.275637; Cos[344] = 0.961262; Sin[345] = -0.258819; Cos[345] = 0.965926; Sin[346] = -0.241922; Cos[346] = 0.970296; Sin[347] = -0.224951; Cos[347] = 0.97437; Sin[348] = -0.207912; Cos[348] = 0.978148; Sin[349] = -0.190809; Cos[349] = 0.981627; Sin[350] = -0.173648; Cos[350] = 0.984808; Sin[351] = -0.156434; Cos[351] = 0.987688; Sin[352] = -0.139173; Cos[352] = 0.990268; Sin[353] = -0.121869; Cos[353] = 0.992546; Sin[354] = -0.104528; Cos[354] = 0.994522; Sin[355] = -0.0871557; Cos[355] = 0.996195; Sin[356] = -0.0697565; Cos[356] = 0.997564; Sin[357] = -0.052336; Cos[357] = 0.99863; Sin[358] = -0.0348995; Cos[358] = 0.999391; Sin[359] = -0.0174524; Cos[359] = 0.999848;

	int width = colorImg.cols;
	int height = colorImg.rows;

	Mat rmat_R[3];
	Mat rmat_G[3];
	Mat rmat_B[3];
	Mat Nmat[3];

	*circle_cnt = 0;
	int dl = min_center_dist*min_center_dist;

	for (int r = max_radius + 1; r >= min_radius - 1; r--)
	{
		int flag = r % 3;
		rmat_R[flag] = Mat(height, width, CV_32SC1, Scalar(0));
		rmat_G[flag] = Mat(height, width, CV_32SC1, Scalar(0));
		rmat_B[flag] = Mat(height, width, CV_32SC1, Scalar(0));
		Nmat[flag] = Mat(height, width, CV_16UC1, Scalar(0));
		int* ptr_rmat_R = (int*)(rmat_R[flag].data);
		int* ptr_rmat_G = (int*)(rmat_G[flag].data);
		int* ptr_rmat_B = (int*)(rmat_B[flag].data);
		ushort* ptr_N = (ushort*)(Nmat[flag].data);

		for (int sita = 359; sita >= 0; sita--)
		{
			float cos_sita = Cos[sita];
			float sin_sita = Sin[sita];
			int row_bias = int(r*sin_sita);
			int col_bias = int(r*cos_sita);
			int row_begin = row_bias >= 0 ? row_bias : 0;
			int row_end = row_bias >= 0 ? height - 1 : height + row_bias - 1;
			int col_begin = col_bias >= 0 ? 0 : -col_bias;
			int col_end = col_bias >= 0 ? width - col_bias - 1 : width - 1;

			for (int row_i = row_end; row_i >= row_begin; row_i--)
			{
				int temp1 = (row_i - row_bias)*width;
				int temp2 = row_i*width;
				for (int col_j = col_end; col_j >= col_begin; col_j--)
				{
					int index1 = temp1 + col_j + col_bias;
					int index2 = temp2 + col_j;
					ptr_rmat_R[index2] += ptr_R[index1];
					ptr_rmat_G[index2] += ptr_G[index1];
					ptr_rmat_B[index2] += ptr_B[index1];
					ptr_N[index2]++;
				}
			}

		}

		for (int row_i = height - 1; row_i >= 0; row_i--)
		{
			int temp = row_i*width;
			for (int col_j = width - 1; col_j >= 0; col_j--)
			{
				int index = temp + col_j;
				int N = ptr_N[index];
				if (N)
				{
					ptr_rmat_R[index] /= N;
					ptr_rmat_G[index] /= N;
					ptr_rmat_B[index] /= N;
				}
			}
		}

		if (r <= max_radius - 1)
		{
			int flag1 = (r + 2) % 3;
			int* ptr_rmat1_R = (int*)(rmat_R[flag1].data);
			int* ptr_rmat1_G = (int*)(rmat_G[flag1].data);
			int* ptr_rmat1_B = (int*)(rmat_B[flag1].data);
			for (int row_i = height - 1; row_i >= 0; row_i--)
			{
				int temp = row_i*width;
				for (int col_j = width - 1; col_j >= 0; col_j--)
				{
					int index = temp + col_j;
					int diff_R = ptr_rmat1_R[index] - ptr_rmat_R[index];
					int diff_G = ptr_rmat1_G[index] - ptr_rmat_G[index];
					int diff_B = ptr_rmat1_B[index] - ptr_rmat_B[index];
					diff_R = diff_R >= 0 ? diff_R : -diff_R;
					diff_G = diff_G >= 0 ? diff_G : -diff_G;
					diff_B = diff_B >= 0 ? diff_B : -diff_B;
					if (diff_R >= 120 || diff_G >= 120 || diff_B >= 120)
					{
						int flag2 = 0;
						for (int k = (*circle_cnt) - 1; k >= 0; k--)
						{
							int dx = x[k] - col_j;
							int dy = y[k] - row_i;
							if (dx*dx + dy*dy <= dl*dl)
							{
								int dr = radius[k] - (r + 1);
								dr = dr >= 0 ? dr : -dr;
								if (dr <= min_radius_dist)
								{
									flag2 = 1;
									break;
								}
							}
						}
						if (!flag2)
						{
							x[*circle_cnt] = col_j;
							y[*circle_cnt] = row_i;
							radius[*circle_cnt] = r;
							(*circle_cnt)++;
						}
					}
				}
			}
		}
	}

#ifdef IMG_SHOW_WZG
	cout << *circle_cnt << endl;
	for (int k = (*circle_cnt) - 1; k >= 0; k--)
	{
		circle(colorImg, Point(x[k], y[k]), radius[k], Scalar(0, 0, 0));
		cout << "x" << x[k] << " y" << y[k] << " r" << radius[k] << endl;
	}
	imshow("circleImg", colorImg);
	waitKey();
#endif

	return MY_OK;
}