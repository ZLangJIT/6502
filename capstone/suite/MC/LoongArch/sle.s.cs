# CS_ARCH_LOONGARCH, CS_MODE_LOONGARCH64, None
0xd8,0x77,0x02,0x74 = xvsle.b $xr24, $xr30, $xr29
0xb7,0xd1,0x02,0x74 = xvsle.h $xr23, $xr13, $xr20
0xea,0x63,0x03,0x74 = xvsle.w $xr10, $xr31, $xr24
0x4d,0xa3,0x03,0x74 = xvsle.d $xr13, $xr26, $xr8
0x6e,0x59,0x82,0x76 = xvslei.b $xr14, $xr11, -0xa
0xc2,0xbe,0x82,0x76 = xvslei.h $xr2, $xr22, 0xf
0xc3,0x31,0x83,0x76 = xvslei.w $xr3, $xr14, 0xc
0xd3,0xab,0x83,0x76 = xvslei.d $xr19, $xr30, 0xa
0x69,0x0b,0x04,0x74 = xvsle.bu $xr9, $xr27, $xr2
0x3d,0xdb,0x04,0x74 = xvsle.hu $xr29, $xr25, $xr22
0x30,0x3b,0x05,0x74 = xvsle.wu $xr16, $xr25, $xr14
0xc5,0xc8,0x05,0x74 = xvsle.du $xr5, $xr6, $xr18
0x51,0x2b,0x84,0x76 = xvslei.bu $xr17, $xr26, 0xa
0x74,0xc9,0x84,0x76 = xvslei.hu $xr20, $xr11, 0x12
0xa1,0x2b,0x85,0x76 = xvslei.wu $xr1, $xr29, 0xa
0xf9,0xe3,0x85,0x76 = xvslei.du $xr25, $xr31, 0x18
