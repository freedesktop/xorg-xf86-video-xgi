/*
 * Mode initializing code (CRT1 section) 
 * (Universal module for Linux kernel framebuffer and XFree86 4.x)
 *
 * Copyright (C) 2001-2004 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License as published by
 * * the Free Software Foundation; either version 2 of the named License,
 * * or any later version.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to endorse or promote products
 * *    derived from this software without specific prior written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESSED OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: 	Thomas Winischhofer <thomas@winischhofer.net>
 *
 * Formerly based on non-functional code-fragements for 300 series by XGI, Inc.
 * Used by permission.
 *
 * TW says: This code looks awful, I know. But please don't do anything about
 * this otherwise debugging will be hell.
 * The code is extremely fragile as regards the different chipsets, different
 * video bridges and combinations thereof. If anything is changed, extreme
 * care has to be taken that that change doesn't break it for other chipsets,
 * bridges or combinations thereof.
 * All comments in this file are by me, regardless if they are marked TW or not.
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "init.h"
#include "vgatypes.h"
#include "vb_def.h"
#include "vb_setmode.h"

/*********************************************/
/*            HELPER: Get ModeID             */
/*********************************************/

USHORT
XGI_GetModeID(ULONG VBFlags, int HDisplay, int VDisplay,
              int Depth, int LCDwidth, int LCDheight)
{
   USHORT ModeIndex = 0;

   switch(HDisplay)
   {
     case 320:
       if(VDisplay == 200)
	   ModeIndex = ModeIndex_320x200[Depth];
       else if(VDisplay == 240)
	   ModeIndex = ModeIndex_320x240[Depth];

       break;
     case 400:
          if(VDisplay == 300) ModeIndex = ModeIndex_400x300[Depth];
          break;
     case 512:
          if(VDisplay == 384) ModeIndex = ModeIndex_512x384[Depth];
          break;
     case 640:
          if(VDisplay == 480)      ModeIndex = ModeIndex_640x480[Depth];
	  else if(VDisplay == 400) ModeIndex = ModeIndex_640x400[Depth];
          break;
     case 720:
          if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 480)      ModeIndex = ModeIndex_720x480[Depth];
             else if(VDisplay == 576) ModeIndex = ModeIndex_720x576[Depth];
          }
          break;
     case 768:
          if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 576) ModeIndex = ModeIndex_768x576[Depth];
          }
	  break;
     case 800:
	  if(VDisplay == 600)    ModeIndex = ModeIndex_800x600[Depth];
	  else if(!(VBFlags & CRT1_LCDA)) {
	     if(VDisplay == 480) ModeIndex = ModeIndex_800x480[Depth];
	  }
          break;
     case 848:
          if(!(VBFlags & CRT1_LCDA)) {
	     if(VDisplay == 480) ModeIndex = ModeIndex_848x480[Depth];
	  }
	  break;
     case 856:
          if(!(VBFlags & CRT1_LCDA)) {
	     if(VDisplay == 480) ModeIndex = ModeIndex_856x480[Depth];
	  }
	  break;
     case 1024:
          if(VDisplay == 768) ModeIndex = ModeIndex_1024x768[Depth];
	  else if(!(VBFlags & CRT1_LCDA)) {
	     if(VDisplay == 576)    ModeIndex = ModeIndex_1024x576[Depth];
	  }
          break;
     case 1152:
          if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 864)    ModeIndex = ModeIndex_1152x864[Depth];
	  }
	  break;
     case 1280:
          if(VDisplay == 1024) ModeIndex = ModeIndex_1280x1024[Depth];
	  else if(VDisplay == 720) {
	     if((VBFlags & CRT1_LCDA) && (LCDwidth == 1280) && (LCDheight == 720)) {
	        ModeIndex = ModeIndex_1280x720[Depth];
	     } else if(!(VBFlags & CRT1_LCDA)) {
	        ModeIndex = ModeIndex_1280x720[Depth];
	     }
	  } else if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 960)      ModeIndex = ModeIndex_1280x960[Depth];
	     else if(VDisplay == 768) {
	           ModeIndex = ModeIndex_310_1280x768[Depth];
	     }
	  }
          break;
     case 1360:
          if(!(VBFlags & CRT1_LCDA)) {
	     if(VDisplay == 768)     ModeIndex = ModeIndex_1360x768[Depth];
	  }
          break;
     case 1400:
          break;
     case 1600:
          if(VDisplay == 1200) ModeIndex = ModeIndex_1600x1200[Depth];
          break;
     case 1680:
          break;
     case 1920:
          if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 1440) ModeIndex = ModeIndex_1920x1440[Depth];
	  }
          break;
     case 2048:
          if(!(VBFlags & CRT1_LCDA)) {
             if(VDisplay == 1536) {
	            ModeIndex = ModeIndex_310_2048x1536[Depth];
	     }
	  }
          break;
   }

   return(ModeIndex);
}

/*********************************************/
/*          HELPER: SetReg, GetReg           */
/*********************************************/

void
XGI_SetReg(XGIIOADDRESS port, USHORT index, USHORT data)
{
   outb(port,index);
   outb(port + 1,data);
}

void
XGI_SetRegByte(XGIIOADDRESS port, USHORT data)
{
   outb(port,data);
}

void
XGI_SetRegShort(XGIIOADDRESS port, USHORT data)
{
   outw(port,data);
}

void
XGI_SetRegLong(XGIIOADDRESS port, ULONG data)
{
    outl(port,data);
}

UCHAR
XGI_GetReg(XGIIOADDRESS port, USHORT index)
{
   outb(port,index);
   return inb(port + 1);
}

UCHAR
XGI_GetRegByte(XGIIOADDRESS port)
{
   return inb(port);
}

USHORT
XGI_GetRegShort(XGIIOADDRESS port)
{
   return inw(port);
}

ULONG
XGI_GetRegLong(XGIIOADDRESS port)
{
   return inl(port);
}

void
XGI_SetRegANDOR(XGIIOADDRESS Port,USHORT Index,USHORT DataAND,USHORT DataOR)
{
  USHORT temp;

  temp = XGI_GetReg(Port,Index);
  temp = (temp & (DataAND)) | DataOR;
  XGI_SetReg(Port,Index,temp);
}

void
XGI_SetRegAND(XGIIOADDRESS Port,USHORT Index,USHORT DataAND)
{
  USHORT temp;

  temp = XGI_GetReg(Port,Index);
  temp &= DataAND;
  XGI_SetReg(Port,Index,temp);
}

void
XGI_SetRegOR(XGIIOADDRESS Port,USHORT Index,USHORT DataOR)
{
  USHORT temp;

  temp = XGI_GetReg(Port,Index);
  temp |= DataOR;
  XGI_SetReg(Port,Index,temp);
}

/*********************************************/
/*      HELPER: DisplayOn, DisplayOff        */
/*********************************************/

void
XGI_New_DisplayOn(XGI_Private *XGI_Pr)
{
   XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x01,0xDF);
}

void
XGI_New_DisplayOff(XGI_Private *XGI_Pr)
{
   XGI_SetRegOR(XGI_Pr->XGI_P3c4,0x01,0x20);
}


/*********************************************/
/*        HELPER: Init Port Addresses        */
/*********************************************/

void
XGIRegInit(XGI_Private *XGI_Pr, XGIIOADDRESS BaseAddr)
{
   XGI_Pr->XGI_P3c4 = BaseAddr + 0x14;
   XGI_Pr->XGI_P3d4 = BaseAddr + 0x24;
   XGI_Pr->XGI_P3c0 = BaseAddr + 0x10;
   XGI_Pr->XGI_P3ce = BaseAddr + 0x1e;
   XGI_Pr->XGI_P3c2 = BaseAddr + 0x12;
   XGI_Pr->XGI_P3ca = BaseAddr + 0x1a;
   XGI_Pr->XGI_P3c6 = BaseAddr + 0x16;
   XGI_Pr->XGI_P3c7 = BaseAddr + 0x17;
   XGI_Pr->XGI_P3c8 = BaseAddr + 0x18;
   XGI_Pr->XGI_P3c9 = BaseAddr + 0x19;
   XGI_Pr->XGI_P3cb = BaseAddr + 0x1b;
   XGI_Pr->XGI_P3cd = BaseAddr + 0x1d;
   XGI_Pr->XGI_P3da = BaseAddr + 0x2a;
   XGI_Pr->XGI_Part1Port = BaseAddr + XGI_CRT2_PORT_04;     /* Digital video interface registers (LCD) */
   XGI_Pr->XGI_Part2Port = BaseAddr + XGI_CRT2_PORT_10;     /* 301 TV Encoder registers */
   XGI_Pr->XGI_Part3Port = BaseAddr + XGI_CRT2_PORT_12;     /* 301 Macrovision registers */
   XGI_Pr->XGI_Part4Port = BaseAddr + XGI_CRT2_PORT_14;     /* 301 VGA2 (and LCD) registers */
   XGI_Pr->XGI_Part5Port = BaseAddr + XGI_CRT2_PORT_14 + 2; /* 301 palette address port registers */
   XGI_Pr->XGI_DDC_Port = BaseAddr + 0x14;                  /* DDC Port ( = P3C4, SR11/0A) */
   XGI_Pr->XGI_VidCapt = BaseAddr + XGI_VIDEO_CAPTURE;
   XGI_Pr->XGI_VidPlay = BaseAddr + XGI_VIDEO_PLAYBACK;
}

/*********************************************/
/*         HELPER: Init PCI & Engines        */
/*********************************************/

static void
XGIInitPCIetc(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo)
{
   switch(HwInfo->jChipType) {
   case XG40:
   case XG42:
   case XG20:
      XGI_SetReg(XGI_Pr->XGI_P3c4,0x20,0xa1);
      /*  - Enable 2D (0x40)
       *  - Enable 3D (0x02)
       *  - Enable 3D vertex command fetch (0x10)
       *  - Enable 3D command parser (0x08)
       *  - Enable 3D G/L transformation engine (0x80)
       */
      XGI_SetRegOR(XGI_Pr->XGI_P3c4,0x1E,0xDA);
      break;
   }
}

/*********************************************/
/*             HELPER: GetVBType             */
/*********************************************/

void
XGI_New_GetVBType(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo)
{
  USHORT flag=0, rev=0, nolcd=0;

  XGI_Pr->XGI_VBType = 0;

  if(XGI_Pr->XGI_IF_DEF_CONEX)
     return;

  flag = XGI_GetReg(XGI_Pr->XGI_Part4Port,0x00);
PDEBUG(ErrorF("GetVBType: part4_0: %x \n",flag)); //yilin
  if(flag > 3) return;

  rev = XGI_GetReg(XGI_Pr->XGI_Part4Port,0x01);
PDEBUG(ErrorF("GetVBType: part4_1: %x \n",rev)); //yilin
  
  if(flag >= 2) {
     XGI_Pr->XGI_VBType = VB_XGI302B;
  } else if(flag == 1) {
     if(rev >= 0xC0) {
       	XGI_Pr->XGI_VBType = VB_XGI301C;
     } else if(rev >= 0xB0) {
       	XGI_Pr->XGI_VBType = VB_XGI301B;
	/* Check if 30xB DH version (no LCD support, use Panel Link instead) */
    	nolcd = XGI_GetReg(XGI_Pr->XGI_Part4Port,0x23);
        if(!(nolcd & 0x02)) XGI_Pr->XGI_VBType |= VB_NoLCD;
     } else {
        XGI_Pr->XGI_VBType = VB_XGI301;
     }
  }
  if(XGI_Pr->XGI_VBType & (VB_XGI301B | VB_XGI301C | VB_XGI302B)) {
     if(rev >= 0xE0) {
	flag = XGI_GetReg(XGI_Pr->XGI_Part4Port,0x39);
	if(flag == 0xff) XGI_Pr->XGI_VBType = VB_XGI302LV;
	else 	 	 XGI_Pr->XGI_VBType = VB_XGI302ELV;
     } else if(rev >= 0xD0) {
	XGI_Pr->XGI_VBType = VB_XGI301LV;
     }
  }
PDEBUG(ErrorF("GetVBType: XGI_Pr->XGI_VBType=%x \n",XGI_Pr->XGI_VBType)); //yilin
}

/*********************************************/
/*           HELPER: SearchModeID            */
/*********************************************/

BOOLEAN
XGI_SearchModeID(const XGI_StStruct *SModeIDTable, 
		 const XGI_ExtStruct *EModeIDTable,
		 unsigned char VGAINFO, USHORT *ModeNo, USHORT *ModeIdIndex)
{
    if (*ModeNo <= 0x13) {
	if ((*ModeNo) <= 0x05)
	    (*ModeNo) |= 0x01;

	for (*ModeIdIndex = 0; /* emtpy */; (*ModeIdIndex)++) {
	    if (SModeIDTable[*ModeIdIndex].St_ModeID == (*ModeNo))
		break;

	    if (SModeIDTable[*ModeIdIndex].St_ModeID == 0xFF)
		return FALSE;
	}

	if (*ModeNo == 0x07) {
	    if (VGAINFO & 0x10) 
		(*ModeIdIndex)++;   /* 400 lines */
	    /* else 350 lines */
	}

	if (*ModeNo <= 0x03) {
	    if (!(VGAINFO & 0x80))
		(*ModeIdIndex)++;

	    if (VGAINFO & 0x10)
		(*ModeIdIndex)++; /* 400 lines  */
	    /* else 350 lines  */
	}
	/* else 200 lines  */
    }
    else {

	for (*ModeIdIndex = 0; /* emtpy */; (*ModeIdIndex)++) {
	    if (EModeIDTable[*ModeIdIndex].Ext_ModeID == (*ModeNo))
		break;

	    if (EModeIDTable[*ModeIdIndex].Ext_ModeID == 0xFF)
		return FALSE;
	}
    }

    return TRUE;
}

/*********************************************/
/*            HELPER: GetModePtr             */
/*********************************************/

UCHAR
XGI_GetModePtr(const XGI_StStruct *SModeIDTable, unsigned ModeType, 
	       USHORT ModeNo, USHORT ModeIdIndex)
{
    return (ModeNo <= 0x13) 
	? SModeIDTable[ModeIdIndex].St_StTableIndex
	: ((ModeType <= 0x02) ? 0x1B /* 02 -> ModeEGA  */ : 0x0F);
}


/*********************************************/
/*           HELPER: LowModeTests            */
/*********************************************/

static BOOLEAN
XGI_DoLowModeTest(XGI_Private *XGI_Pr, USHORT ModeNo, PXGI_HW_DEVICE_INFO HwInfo)
{
    USHORT temp,temp1,temp2;

    if((ModeNo != 0x03) && (ModeNo != 0x10) && (ModeNo != 0x12))
       return(1);
    temp = XGI_GetReg(XGI_Pr->XGI_P3d4,0x11);
    XGI_SetRegOR(XGI_Pr->XGI_P3d4,0x11,0x80);
    temp1 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x00);
    XGI_SetReg(XGI_Pr->XGI_P3d4,0x00,0x55);
    temp2 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x00);
    XGI_SetReg(XGI_Pr->XGI_P3d4,0x00,temp1);
    XGI_SetReg(XGI_Pr->XGI_P3d4,0x11,temp);
    if (temp2 == 0x55)
	return(0);
    else 
	return(1);
}

static void
XGI_SetLowModeTest(XGI_Private *XGI_Pr, USHORT ModeNo, PXGI_HW_DEVICE_INFO HwInfo)
{
    if(XGI_DoLowModeTest(XGI_Pr, ModeNo, HwInfo)) {
       XGI_Pr->XGI_SetFlag |= LowModeTests;
    }
}

static void
XGI_HandleCRT1(XGI_Private *XGI_Pr)
{
    XGI_SetRegAND(XGI_Pr->XGI_P3d4, 0x53, 0xbf);
}

/*********************************************/
/*           HELPER: GetColorDepth           */
/*********************************************/

USHORT
XGI_New_GetColorDepth(XGI_Private *XGI_Pr, USHORT ModeNo, USHORT ModeIdIndex)
{
  USHORT ColorDepth[6] = { 1, 2, 4, 4, 6, 8};
  SHORT  index;
  USHORT modeflag;

    if(ModeNo <= 0x13)
        modeflag = XGI_Pr->XGI_SModeIDTable[ModeIdIndex].St_ModeFlag;
    else
        modeflag = XGI_Pr->XGI_EModeIDTable[ModeIdIndex].Ext_ModeFlag;

  index = (modeflag & ModeInfoFlag) - ModeEGA;
  if(index < 0) index = 0;
  return(ColorDepth[index]);
}

/*********************************************/
/*             HELPER: GetOffset             */
/*********************************************/

USHORT
XGI_New_GetOffset(XGI_Private *XGI_Pr,USHORT ModeNo,USHORT ModeIdIndex,
              USHORT RefreshRateTableIndex,PXGI_HW_DEVICE_INFO HwInfo)
{
  USHORT xres, temp, colordepth, infoflag;

  infoflag = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
  xres = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].XRes;

  colordepth = XGI_New_GetColorDepth(XGI_Pr,ModeNo,ModeIdIndex);

  temp = xres / 16;
  if(infoflag & InterlaceMode) temp <<= 1;
  temp *= colordepth;
  if(xres % 16) {
     colordepth >>= 1;
     temp += colordepth;
  }

  return(temp);
}

/*********************************************/
/*                   SEQ                     */
/*********************************************/

static void
XGI_New_SetSeqRegs(XGI_Private *XGI_Pr, USHORT StandTableIndex, PXGI_HW_DEVICE_INFO HwInfo)
{
   UCHAR SRdata;
   USHORT i;

   XGI_SetReg(XGI_Pr->XGI_P3c4,0x00,0x03);           	/* Set SR0  */

   SRdata = XGI_Pr->XGI_StandTable[StandTableIndex].SR[0];

   if(XGI_Pr->XGI_VBType & VB_XGI301BLV302BLV) {
      if(XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA) {
         SRdata |= 0x01;
      }

       if(XGI_Pr->XGI_VBInfo & (SetCRT2ToLCD | SetCRT2ToTV)) {
	   if(XGI_Pr->XGI_VBInfo & SetInSlaveMode) {
               SRdata |= 0x01;          		/* 8 dot clock  */
	   }
       }
   }

   SRdata |= 0x20;                			/* screen off  */

   XGI_SetReg(XGI_Pr->XGI_P3c4,0x01,SRdata);

   for(i = 2; i <= 4; i++) {
      SRdata = XGI_Pr->XGI_StandTable[StandTableIndex].SR[i-1];
      XGI_SetReg(XGI_Pr->XGI_P3c4,i,SRdata);
   }
}

/*********************************************/
/*                  MISC                     */
/*********************************************/

static void
XGI_New_SetMiscRegs(XGI_Private *XGI_Pr, USHORT StandTableIndex, PXGI_HW_DEVICE_INFO HwInfo)
{
   UCHAR Miscdata;

   Miscdata = XGI_Pr->XGI_StandTable[StandTableIndex].MISC;

   XGI_SetRegByte(XGI_Pr->XGI_P3c2,Miscdata);
}

/*********************************************/
/*                  CRTC                     */
/*********************************************/

static void
XGI_New_SetCRTCRegs(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
                USHORT StandTableIndex)
{
  UCHAR CRTCdata;
  USHORT i;

  XGI_SetRegAND(XGI_Pr->XGI_P3d4,0x11,0x7f);                       /* Unlock CRTC */

  for(i = 0; i <= 0x18; i++) {
     CRTCdata = XGI_Pr->XGI_StandTable[StandTableIndex].CRTC[i];
     XGI_SetReg(XGI_Pr->XGI_P3d4,i,CRTCdata);                     /* Set CRTC(3d4) */
  }

}

/*********************************************/
/*                   ATT                     */
/*********************************************/

static void
XGI_New_SetATTRegs(XGI_Private *XGI_Pr, USHORT StandTableIndex,
               PXGI_HW_DEVICE_INFO HwInfo)
{
   UCHAR ARdata;
   USHORT i;

   for(i = 0; i <= 0x13; i++) {
      ARdata = XGI_Pr->XGI_StandTable[StandTableIndex].ATTR[i];

      if(i == 0x13) {
         /* Pixel shift. If screen on LCD or TV is shifted left or right,
          * this might be the cause.
          */
         if(XGI_Pr->XGI_VBType & VB_XGI301BLV302BLV) {
            if(XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA)  ARdata=0;
         }
      }
      XGI_GetRegByte(XGI_Pr->XGI_P3da);                         /* reset 3da  */
      XGI_SetRegByte(XGI_Pr->XGI_P3c0,i);                       /* set index  */
      XGI_SetRegByte(XGI_Pr->XGI_P3c0,ARdata);                  /* set data   */
   }
   XGI_GetRegByte(XGI_Pr->XGI_P3da);                            /* reset 3da  */
   XGI_SetRegByte(XGI_Pr->XGI_P3c0,0x14);                       /* set index  */
   XGI_SetRegByte(XGI_Pr->XGI_P3c0,0x00);                       /* set data   */

   XGI_GetRegByte(XGI_Pr->XGI_P3da);
   XGI_SetRegByte(XGI_Pr->XGI_P3c0,0x20);			/* Enable Attribute  */
   XGI_GetRegByte(XGI_Pr->XGI_P3da);
}

/*********************************************/
/*                   GRC                     */
/*********************************************/

static void
XGI_New_SetGRCRegs(XGI_Private *XGI_Pr, USHORT StandTableIndex)
{
   UCHAR GRdata;
   USHORT i;

   for(i = 0; i <= 0x08; i++) {
      GRdata = XGI_Pr->XGI_StandTable[StandTableIndex].GRC[i];
      XGI_SetReg(XGI_Pr->XGI_P3ce,i,GRdata);
   }

   if(XGI_Pr->XGI_ModeType > ModeVGA) {
      /* 256 color disable */
      XGI_SetRegAND(XGI_Pr->XGI_P3ce,0x05,0xBF);
   }
}

/*********************************************/
/*          CLEAR EXTENDED REGISTERS         */
/*********************************************/

static void
XGI_New_ClearExt1Regs(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo, USHORT ModeNo)
{
  USHORT i;

  for(i = 0x0A; i <= 0x0E; i++) {
     XGI_SetReg(XGI_Pr->XGI_P3c4,i,0x00);
  }

    XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x37,0xFE);
    if(ModeNo <= 0x13) {
        if(ModeNo == 0x06 || ModeNo >= 0x0e) {
	    XGI_SetReg(XGI_Pr->XGI_P3c4,0x0e,0x20);
	}
    }
}

/*********************************************/
/*                 RESET VCLK                */
/*********************************************/

static void
XGI_ResetCRT1VCLK(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo)
{
    XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x31,0xCF,0x20);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2B,XGI_Pr->XGI_VCLKData[1].SR2B);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2C,XGI_Pr->XGI_VCLKData[1].SR2C);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2D,0x80);
    XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x31,0xcf,0x10);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2B,XGI_Pr->XGI_VCLKData[0].SR2B);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2C,XGI_Pr->XGI_VCLKData[0].SR2C);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2D,0x80);
}

/*********************************************/
/*                  SYNC                     */
/*********************************************/

static void
XGI_SetCRT1Sync(XGI_Private *XGI_Pr, USHORT RefreshRateTableIndex)
{
  USHORT sync;

  sync = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].Ext_InfoFlag >> 8;
  sync &= 0xC0;
  sync |= 0x2f;
  XGI_SetRegByte(XGI_Pr->XGI_P3c2,sync);
}

/*********************************************/
/*                  CRTC/2                   */
/*********************************************/

static void
XGI_New_SetCRT1CRTC(XGI_Private *XGI_Pr, USHORT ModeNo, USHORT ModeIdIndex,
                USHORT RefreshRateTableIndex,
		PXGI_HW_DEVICE_INFO HwInfo)
{
  UCHAR  index;
  USHORT temp,i,j,modeflag;

  XGI_SetRegAND(XGI_Pr->XGI_P3d4,0x11,0x7f);		/* unlock cr0-7 */

     if(ModeNo <= 0x13) {
        modeflag = XGI_Pr->XGI_SModeIDTable[ModeIdIndex].St_ModeFlag;
     } else {
        modeflag = XGI_Pr->XGI_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
     }

     index = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].Ext_CRT1CRTC;

     for(i=0,j=0;i<=7;i++,j++) {
        XGI_SetReg(XGI_Pr->XGI_P3d4,j,XGI_Pr->XGI_CRT1Table[index].CR[i]);
     }
     for(j=0x10;i<=10;i++,j++) {
        XGI_SetReg(XGI_Pr->XGI_P3d4,j,XGI_Pr->XGI_CRT1Table[index].CR[i]);
     }
     for(j=0x15;i<=12;i++,j++) {
        XGI_SetReg(XGI_Pr->XGI_P3d4,j,XGI_Pr->XGI_CRT1Table[index].CR[i]);
     }
     for(j=0x0A;i<=15;i++,j++) {
        XGI_SetReg(XGI_Pr->XGI_P3c4,j,XGI_Pr->XGI_CRT1Table[index].CR[i]);
     }

     temp = XGI_Pr->XGI_CRT1Table[index].CR[16] & 0xE0;
     XGI_SetReg(XGI_Pr->XGI_P3c4,0x0E,temp);

     temp = ((XGI_Pr->XGI_CRT1Table[index].CR[16]) & 0x01) << 5;
     if(modeflag & DoubleScanMode)  temp |= 0x80;
     XGI_SetRegANDOR(XGI_Pr->XGI_P3d4,0x09,0x5F,temp);

  if(XGI_Pr->XGI_ModeType > ModeVGA) XGI_SetReg(XGI_Pr->XGI_P3d4,0x14,0x4F);
}

/*********************************************/
/*               OFFSET & PITCH              */
/*********************************************/
/*  (partly overruled by SetPitch() in XF86) */
/*********************************************/

static void
XGI_New_SetCRT1Offset(XGI_Private *XGI_Pr, USHORT ModeNo, USHORT ModeIdIndex,
                  USHORT RefreshRateTableIndex,
		  PXGI_HW_DEVICE_INFO HwInfo)
{
   USHORT temp, DisplayUnit, infoflag;

   infoflag = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;

   DisplayUnit = XGI_New_GetOffset(XGI_Pr,ModeNo,ModeIdIndex,
                     	       RefreshRateTableIndex,HwInfo);

   temp = (DisplayUnit >> 8) & 0x0f;
   XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x0E,0xF0,temp);

   temp = DisplayUnit & 0xFF;
   XGI_SetReg(XGI_Pr->XGI_P3d4,0x13,temp);

   if(infoflag & InterlaceMode) DisplayUnit >>= 1;

   DisplayUnit <<= 5;
   temp = (DisplayUnit & 0xff00) >> 8;
   if(DisplayUnit & 0xff) temp++;
   temp++;
   XGI_SetReg(XGI_Pr->XGI_P3c4,0x10,temp);
}

/*********************************************/
/*                  VCLK                     */
/*********************************************/

static void
XGI_New_SetCRT1VCLK(XGI_Private *XGI_Pr, USHORT ModeNo, USHORT ModeIdIndex,
                PXGI_HW_DEVICE_INFO HwInfo, USHORT RefreshRateTableIndex)
{
  USHORT  index=0, clka, clkb;

     if((XGI_Pr->XGI_VBType & VB_XGI301BLV302BLV) && (XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA)) {
        clka = XGI_Pr->XGI_VBVCLKData[index].Part4_A;
	clkb = XGI_Pr->XGI_VBVCLKData[index].Part4_B;
     } else {
        clka = XGI_Pr->XGI_VCLKData[index].SR2B;
	clkb = XGI_Pr->XGI_VCLKData[index].SR2C;
     }

    XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x31,0xCF);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2B,clka);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2C,clkb);
    XGI_SetReg(XGI_Pr->XGI_P3c4,0x2D,0x01);
}

/*********************************************/
/*              MODE REGISTERS               */
/*********************************************/

static void
XGI_New_SetVCLKState(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
                 USHORT ModeNo, USHORT RefreshRateTableIndex,
                 USHORT ModeIdIndex)
{
  USHORT data=0, VCLK=0, index=0;

  if(ModeNo > 0x13) {
        VCLK = XGI_Pr->XGI_VCLKData[index].CLOCK;
  }

    if(VCLK >= 166)
	data |= 0x0c;

    XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x32,0xf3,data);

    if(VCLK >= 166) {
	XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x1f,0xe7);
    }

    /* DAC speed */
    XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x07,0xE8,0x10);
}

static void
XGI_New_SetCRT1ModeRegs(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
                    USHORT ModeNo,USHORT ModeIdIndex,USHORT RefreshRateTableIndex)
{
  USHORT data,infoflag=0,modeflag;
  USHORT resindex = 0,xres;

     if(ModeNo > 0x13) {
    	modeflag = XGI_Pr->XGI_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
    	infoflag = XGI_Pr->XGI_RefIndex[RefreshRateTableIndex].Ext_InfoFlag;
	xres = XGI_Pr->XGI_ModeResInfo[resindex].HTotal;
     } else {
    	modeflag = XGI_Pr->XGI_SModeIDTable[ModeIdIndex].St_ModeFlag;
	xres = XGI_Pr->XGI_StResInfo[resindex].HTotal;
     }

  /* Disable DPMS */
  XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x1F,0x3F);

  data = 0;
  if(ModeNo > 0x13) {
     if(XGI_Pr->XGI_ModeType > 0x02) {
        data |= 0x02;
        data |= ((XGI_Pr->XGI_ModeType - ModeVGA) << 2);
     }
     if(infoflag & InterlaceMode) data |= 0x20;
  }
  XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x06,0xC0,data);

    data = 0;
    if(infoflag & InterlaceMode) {
        if(xres <= 800)       data = 0x0020;
        else if(xres <= 1024) data = 0x0035;
        else                  data = 0x0048;
    }
    XGI_SetReg(XGI_Pr->XGI_P3d4,0x19,(data & 0xFF));
    XGI_SetRegANDOR(XGI_Pr->XGI_P3d4,0x1a,0xFC,(data >> 8));

  if(modeflag & HalfDCLK) {
     XGI_SetRegOR(XGI_Pr->XGI_P3c4,0x01,0x08);
  }

  data = 0;
  if(modeflag & LineCompareOff) data = 0x08;

     XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x0F,0xB7,data);
     if(XGI_Pr->XGI_ModeType == ModeEGA) {
        if(ModeNo > 0x13) {
  	   XGI_SetRegOR(XGI_Pr->XGI_P3c4,0x0F,0x40);
        }
     }

    XGI_SetRegAND(XGI_Pr->XGI_P3c4,0x31,0xfb);

  data = 0x60;
  if(XGI_Pr->XGI_ModeType != ModeText) {
     data ^= 0x60;
     if(XGI_Pr->XGI_ModeType != ModeEGA) {
        data ^= 0xA0;
     }
  }
  XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x21,0x1F,data);

  XGI_New_SetVCLKState(XGI_Pr, HwInfo, ModeNo, RefreshRateTableIndex, ModeIdIndex);
}

/*********************************************/
/*                 LOAD DAC                  */
/*********************************************/

extern const uint8_t XGI_MDA_DAC[];
extern const uint8_t XGI_CGA_DAC[];
extern const uint8_t XGI_EGA_DAC[];
extern const uint8_t XGI_VGA_DAC[];

void
XGI_New_LoadDAC(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
            USHORT ModeNo, USHORT ModeIdIndex)
{
   USHORT data,data2;
   USHORT time,i,j,k,m,n,o;
   USHORT si,di,bx,dl,al,ah,dh;
   USHORT shiftflag;
   XGIIOADDRESS DACAddr, DACData;
   const uint8_t *table = NULL;

   if(ModeNo <= 0x13) {
      data = XGI_Pr->XGI_SModeIDTable[ModeIdIndex].St_ModeFlag;
   } else {
      data = XGI_Pr->XGI_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }

   data &= DACInfoFlag;
   time = 64;
   if(data == 0x00) table = XGI_MDA_DAC;
   if(data == 0x08) table = XGI_CGA_DAC;
   if(data == 0x10) table = XGI_EGA_DAC;
   if(data == 0x18) {
      time = 256;
      table = XGI_VGA_DAC;
   }
   if(time == 256) j = 16;
   else            j = time;

   if( ( (XGI_Pr->XGI_VBInfo & SetCRT2ToLCD) &&        /* 301B-DH LCD */
         (XGI_Pr->XGI_VBType & VB_NoLCD) )        ||
       (XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA)       ||   /* LCDA */
       (!(XGI_Pr->XGI_SetFlag & ProgrammingCRT2)) ) {  /* Programming CRT1 */
      DACAddr = XGI_Pr->XGI_P3c8;
      DACData = XGI_Pr->XGI_P3c9;
      shiftflag = 0;
      XGI_SetRegByte(XGI_Pr->XGI_P3c6,0xFF);
   } else {
      shiftflag = 1;
      DACAddr = XGI_Pr->XGI_Part5Port;
      DACData = XGI_Pr->XGI_Part5Port + 1;
   }

   XGI_SetRegByte(DACAddr,0x00);

   for(i=0; i<j; i++) {
      data = table[i];
      for(k=0; k<3; k++) {
	data2 = 0;
	if(data & 0x01) data2 = 0x2A;
	if(data & 0x02) data2 += 0x15;
	if(shiftflag) data2 <<= 2;
	XGI_SetRegByte(DACData, data2);
	data >>= 2;
      }
   }

   if(time == 256) {
      for(i = 16; i < 32; i++) {
   	 data = table[i];
	 if(shiftflag) data <<= 2;
	 for(k = 0; k < 3; k++) XGI_SetRegByte(DACData, data);
      }
      si = 32;
      for(m = 0; m < 9; m++) {
         di = si;
         bx = si + 4;
         dl = 0;
         for(n = 0; n < 3; n++) {
  	    for(o = 0; o < 5; o++) {
	       dh = table[si];
	       ah = table[di];
	       al = table[bx];
	       si++;
	       XGI_WriteDAC(DACData, shiftflag, dl, ah, al, dh);
	    }
	    si -= 2;
	    for(o = 0; o < 3; o++) {
	       dh = table[bx];
	       ah = table[di];
	       al = table[si];
	       si--;
	       XGI_WriteDAC(DACData, shiftflag, dl, ah, al, dh);
	    }
	    dl++;
	 }            /* for n < 3 */
	 si += 5;
      }               /* for m < 9 */
   }
}

/*********************************************/
/*         SET CRT1 REGISTER GROUP           */
/*********************************************/

static void
XGI_New_SetCRT1Group(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
                 USHORT ModeNo, USHORT ModeIdIndex)
{
    const USHORT StandTableIndex = XGI_GetModePtr(XGI_Pr->XGI_SModeIDTable,
						  XGI_Pr->XGI_ModeType,
						  ModeNo, ModeIdIndex);
    USHORT RefreshRateTableIndex = 0;

    XGI_Pr->XGI_CRT1Mode = ModeNo;

/*
  if(XGI_Pr->XGI_SetFlag & LowModeTests) {
     if(XGI_Pr->XGI_VBInfo & (SetSimuScanMode | SwitchToCRT2)) {
        XGI_New_DisableBridge(XGI_Pr, HwInfo);
     }
  }
*/
  XGI_New_SetSeqRegs(XGI_Pr, StandTableIndex, HwInfo);
  XGI_New_SetMiscRegs(XGI_Pr, StandTableIndex, HwInfo);
  XGI_New_SetCRTCRegs(XGI_Pr, HwInfo, StandTableIndex);
  XGI_New_SetATTRegs(XGI_Pr, StandTableIndex, HwInfo);
  XGI_New_SetGRCRegs(XGI_Pr, StandTableIndex);
  XGI_New_ClearExt1Regs(XGI_Pr, HwInfo, ModeNo);
  XGI_ResetCRT1VCLK(XGI_Pr, HwInfo);

  XGI_Pr->XGI_SelectCRT2Rate = 0;
  XGI_Pr->XGI_SetFlag &= (~ProgrammingCRT2);

#ifdef LINUX_XF86
  xf86DrvMsgVerb(0, X_PROBED, 4, "(init: VBType=0x%04x, VBInfo=0x%04x)\n",
                    XGI_Pr->XGI_VBType, XGI_Pr->XGI_VBInfo);
#endif

  if(XGI_Pr->XGI_VBInfo & SetSimuScanMode) {
     if(XGI_Pr->XGI_VBInfo & SetInSlaveMode) {
        XGI_Pr->XGI_SetFlag |= ProgrammingCRT2;
     }
  }

  if(XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA) {
     XGI_Pr->XGI_SetFlag |= ProgrammingCRT2;
  }

  if(!(XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA)) {
     XGI_Pr->XGI_SetFlag &= ~ProgrammingCRT2;
  }

  if(RefreshRateTableIndex != 0xFFFF) {
     XGI_SetCRT1Sync(XGI_Pr, RefreshRateTableIndex);
     XGI_New_SetCRT1CRTC(XGI_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex, HwInfo);
     XGI_New_SetCRT1Offset(XGI_Pr, ModeNo, ModeIdIndex, RefreshRateTableIndex, HwInfo);
     XGI_New_SetCRT1VCLK(XGI_Pr, ModeNo, ModeIdIndex, HwInfo, RefreshRateTableIndex);
  }

  XGI_New_SetCRT1ModeRegs(XGI_Pr, HwInfo, ModeNo, ModeIdIndex, RefreshRateTableIndex);

  XGI_New_LoadDAC(XGI_Pr, HwInfo, ModeNo, ModeIdIndex);
}


/*********************************************/
/*         XFree86: SET SCREEN PITCH         */
/*********************************************/

#ifdef LINUX_XF86
static void
XGI_SetPitchCRT1(XGI_Private *XGI_Pr, ScrnInfoPtr pScrn)
{
   XGIPtr pXGI = XGIPTR(pScrn);
   UShort HDisplay = pXGI->scrnPitch >> 3;

   XGI_SetReg(XGI_Pr->XGI_P3d4,0x13,(HDisplay & 0xFF));
   XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x0E,0xF0,(HDisplay>>8));
}


static void
XGI_SetPitch(XGI_Private *XGI_Pr, ScrnInfoPtr pScrn)
{
   XGIPtr pXGI = XGIPTR(pScrn);
   BOOLEAN isslavemode = FALSE;

   /* We need to set pitch for CRT1 if bridge is in slave mode, too */
   if((pXGI->VBFlags & DISPTYPE_DISP1) || (isslavemode)) {
      XGI_SetPitchCRT1(XGI_Pr, pScrn);
   }
}
#endif

/*********************************************/
/*          XFree86: XGIBIOSSetMode()        */
/*           for non-Dual-Head mode          */
/*********************************************/

#ifdef LINUX_XF86
BOOLEAN
XGIBIOSSetMode(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
	       ScrnInfoPtr pScrn, DisplayModePtr mode)
{
    XGIPtr  pXGI = XGIPTR(pScrn);
    UShort  ModeNo=0;
    BOOLEAN SetModeRet = FALSE ;
    UShort  HDisplay = pXGI->scrnOffset >> 3 ;
#if XGI_USING_BIOS_SETMODE
    xf86Int10InfoPtr pInt = NULL ; /* Our int10 */
#endif
    
    ModeNo = XGI_CalcModeIndex(pScrn, mode, pXGI->VBFlags);
    if(!ModeNo) return FALSE;
    
    xf86DrvMsgVerb(pScrn->scrnIndex, X_INFO, 3, "Setting standard mode 0x%x\n", ModeNo);
    
    PDEBUG(ErrorF("C code setmode: ModeNo: 0x%08lX \n",ModeNo));
    
    /* PDEBUG(XGIDumpRegs(pScrn)) ; */
    /*
        return(XGISetMode(XGI_Pr, HwInfo, pScrn, ModeNo, TRUE));
    */
    
    /*
    if( ModeNo <= 13 )
        outXGIIDXREG(XGISR, 0x20, 0x21);
    else
        outXGIIDXREG(XGISR, 0x20, 0xAD);
    */
    /* outXGIIDXREG(XGISR, 0x1E, 0xDA); */

#if XGI_USING_BIOS_SETMODE
       PDEBUG(ErrorF("XGI_USING_BIOS_SETMODE \n"));
    if(pXGI->pVbe)
	{
		pInt = pXGI->pVbe->pInt10 ;
	}

	if(pInt)
	{
		
		if(xf86LoadSubModule(pScrn, "int10")) {
	   		pInt->num = 0x10 ;
			pInt->ax = 0x80 | ModeNo ;
			/* ah = 0 , set mode */
			xf86ExecX86int10(pInt) ;
			if( (pInt->ax & 0x7f) == ModeNo) 
			{
				SetModeRet = TRUE ;
			}
		}
	}
	else
#endif
	{
	       PDEBUG(ErrorF("XGI_USING_C_code_SETMODE \n"));	
    	SetModeRet = XGISetModeNew( HwInfo, ModeNo );
	       PDEBUG(ErrorF("out_of_C_code_SETMODE \n"));
	}
    
    
    if(pScrn) {
        /* SetPitch: Adapt to virtual size & position */
        if (ModeNo > 0x13) {
            /* XGI_SetPitch(XGI_Pr, pScrn); */

            XGI_SetReg(XGI_Pr->XGI_Part1Port, 0x2f, 1);  //yilin for crt2pitch it shoude modify if not colone mode
            XGI_SetReg(XGI_Pr->XGI_Part1Port, 0x07, (HDisplay & 0xFF));
            XGI_SetRegANDOR(XGI_Pr->XGI_Part1Port, 0x09, 0xF0, (HDisplay>>8)); 
            
            XGI_SetReg(XGI_Pr->XGI_P3d4,0x13,(HDisplay & 0xFF));
            XGI_SetRegANDOR(XGI_Pr->XGI_P3c4,0x0E,0xF0,(HDisplay>>8));
        }
        /* Backup/Set ModeNo in BIOS scratch area */
        /* XGI_GetSetModeID(pScrn, ModeNo); */
    }

/*    XGI_SetReg(XGI_Pr->XGI_Part1Port,0x2F,1); //yilin test
    XGI_SetReg(XGI_Pr->XGI_Part1Port,0x03,0x41);
    XGI_SetReg(XGI_Pr->XGI_Part1Port,0x07,(0x00 & 0xFF));
    
       XGI_SetRegANDOR(XGI_Pr->XGI_Part1Port,0x09,0xF0,(0x02));

*/
    
    return SetModeRet ;
    /* return (XGISetModeNew( HwInfo, ModeNo )); */
}

/*********************************************/
/*       XFree86: XGIBIOSSetModeCRT1()       */
/*           for Dual-Head modes             */
/*********************************************/

BOOLEAN
XGIBIOSSetModeCRT1(XGI_Private *XGI_Pr, PXGI_HW_DEVICE_INFO HwInfo,
		   ScrnInfoPtr pScrn, DisplayModePtr mode)
{
   XGIPtr  pXGI = XGIPTR(pScrn);
   XGIIOADDRESS BaseAddr = HwInfo->pjIOAddress;
   USHORT  ModeIdIndex, ModeNo=0;
   UCHAR backupreg=0;
#ifdef XGIDUALHEAD
   XGIEntPtr pXGIEnt = pXGI->entityPrivate;
   UCHAR backupcr30, backupcr31, backupcr38, backupcr35, backupp40d=0;
#endif

   {

         ModeNo = XGI_CalcModeIndex(pScrn, mode, pXGI->VBFlags);
         if(!ModeNo) return FALSE;

         xf86DrvMsgVerb(pScrn->scrnIndex, X_INFO, 3,
	 	"Setting standard mode 0x%x on CRT1\n", ModeNo);
   }

   XGIRegInit(XGI_Pr, BaseAddr);
#if (defined(i386) || defined(__i386) || defined(__i386__) || defined(__AMD64__))
   XGI_Pr->XGI_VGAINFO = XGI_GetSetBIOSScratch(pScrn, 0x489, 0xff);
#else
   XGI_Pr->XGI_VGAINFO = 0x11;
#endif
   XGIInitPCIetc(XGI_Pr, HwInfo);

   XGI_SetReg(XGI_Pr->XGI_P3c4,0x05,0x86);

   if (!XGI_SearchModeID(XGI_Pr->XGI_SModeIDTable,
			 XGI_Pr->XGI_EModeIDTable,
			 XGI_Pr->XGI_VGAINFO, &ModeNo, &ModeIdIndex)) {
       return FALSE;
   }

   /* Determine VBType */
   XGI_New_GetVBType(XGI_Pr, HwInfo);

    if (XGI_Pr->XGI_VBType & VB_XGI301BLV302BLV) {
	backupreg = XGI_GetReg(XGI_Pr->XGI_P3d4,0x38);
    }

   /* Get VB information (connectors, connected devices) */
   /* (We don't care if the current mode is a CRT2 mode) */
   XGI_SetLowModeTest(XGI_Pr, ModeNo, HwInfo);

   /* Set mode on CRT1 */
   XGI_New_SetCRT1Group(XGI_Pr, HwInfo, ModeNo, ModeIdIndex);
   /* SetPitch: Adapt to virtual size & position */
   XGI_SetPitchCRT1(XGI_Pr, pScrn);

#ifdef XGIDUALHEAD
   if(pXGI->DualHeadMode) {
      pXGIEnt->CRT1ModeNo = ModeNo;
      pXGIEnt->CRT1DMode = mode;
   }
#endif


   /* Reset CRT2 if changing mode on CRT1 */
#ifdef XGIDUALHEAD
   if(pXGI->DualHeadMode) {
      if(pXGIEnt->CRT2ModeNo != -1) {
         xf86DrvMsgVerb(pScrn->scrnIndex, X_INFO, 3,
				"(Re-)Setting mode for CRT2\n");
	 backupcr30 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x30);
	 backupcr31 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x31);
	 backupcr35 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x35);
	 backupcr38 = XGI_GetReg(XGI_Pr->XGI_P3d4,0x38);
	 if(XGI_Pr->XGI_VBType & VB_XGIVB) {
	    /* Backup LUT-enable */
	    if(pXGIEnt->CRT2ModeSet) {
	       backupp40d = XGI_GetReg(XGI_Pr->XGI_Part4Port,0x0d) & 0x08;
	    }
	 }
	 if(XGI_Pr->XGI_VBInfo & SetCRT2ToLCDA) {
	    XGI_SetReg(XGI_Pr->XGI_P3d4,0x30,pXGIEnt->CRT2CR30);
	    XGI_SetReg(XGI_Pr->XGI_P3d4,0x31,pXGIEnt->CRT2CR31);
	    XGI_SetReg(XGI_Pr->XGI_P3d4,0x35,pXGIEnt->CRT2CR35);
	    XGI_SetReg(XGI_Pr->XGI_P3d4,0x38,pXGIEnt->CRT2CR38);
	 }
	
         XGI_SetReg(XGI_Pr->XGI_P3d4,0x30,backupcr30);
	 XGI_SetReg(XGI_Pr->XGI_P3d4,0x31,backupcr31);
	 XGI_SetReg(XGI_Pr->XGI_P3d4,0x35,backupcr35);
	 XGI_SetReg(XGI_Pr->XGI_P3d4,0x38,backupcr38);
	 if(XGI_Pr->XGI_VBType & VB_XGIVB) {
	    XGI_SetRegANDOR(XGI_Pr->XGI_Part4Port,0x0d, ~0x08, backupp40d);
	 }
      }
   }
#endif

   /* Warning: From here, the custom mode entries in XGI_Pr are
    * possibly overwritten
    */

   XGI_HandleCRT1(XGI_Pr);

   XGI_New_DisplayOn(XGI_Pr);
   XGI_SetRegByte(XGI_Pr->XGI_P3c6,0xFF);

   /* Backup/Set ModeNo in BIOS scratch area */
   XGI_GetSetModeID(pScrn,ModeNo);

   return TRUE;
}
#endif /* Linux_XF86 */
