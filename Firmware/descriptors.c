/******************************************************************************
 * @file     descriptors.c
 * @brief    NUC100 series USBD descriptor
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NUC100Series.h"
#include "usbd.h"
#include "usb_hid.h"

uint8_t ReportDescriptor[] =
{
  HID_UsagePageVendor( 0x00                      ),
  HID_Usage          ( 0x01                      ),
  HID_Collection     ( HID_Application           ),
    HID_LogicalMin   ( 0                         ), /* value range: 0 - 0xFF */
    HID_LogicalMaxS  ( 0xFF                      ),
    HID_ReportSize   ( 8                         ), /* 8 bits */
    HID_ReportCount  ( 64  ),
    HID_Usage        ( 0x01                      ),
    HID_Input        ( HID_Data | HID_Variable | HID_Absolute ),
    HID_ReportCount  ( 64 ),
    HID_Usage        ( 0x01                      ),
    HID_Output       ( HID_Data | HID_Variable | HID_Absolute ),
    HID_ReportCount  ( 1),
    HID_Usage        ( 0x01                      ),
    HID_Feature      ( HID_Data | HID_Variable | HID_Absolute ),
  HID_EndCollection,
};




/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] =
{
	LEN_DEVICE,     /* bLength */
	DESC_DEVICE,    /* bDescriptorType */
	0x10, 0x01,     /* bcdUSB */
	0x00,           /* bDeviceClass */
	0x00,           /* bDeviceSubClass */
	0x00,           /* bDeviceProtocol */
	8,   /* bMaxPacketSize0 */
	/* idVendor */
	0x0D28 & 0x00FF,
	(0x0D28 & 0xFF00) >> 8,
	/* idProduct */
	0x0204 & 0x00FF,
	(0x0204 & 0xFF00) >> 8,
	/* bcdDevice */	
	0x0100 & 0x00FF,
	(0x0100 & 0xFF00) >> 8,
	0x01,           /* iManufacture */
	0x02,           /* iProduct */
	0x03,           /* iSerialNumber - no serial */
	0x01            /* bNumConfigurations */
};

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] =
{
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    41 & 0x00FF,                
    (41 & 0xFF00) >> 8,
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (0 << 6),/* bmAttributes */
    0xfa,         /* MaxPower */
	
	/* Interface, Alternate Setting 0, HID Class */
	9,										/* bLength */                                                       \
	4,										/* bDescriptorType */                                               \
	0,										/* bInterfaceNumber */                                              \
	0x00,									/* bAlternateSetting */                                             \
	0x02,									/* bNumEndpoints */                                                 \
	3,     /* bInterfaceClass */                                               \
	0,                    /* bInterfaceSubClass */                                            \
	0,                    /* bInterfaceProtocol */                                            \
	0,                  /* iInterface */    
		
    /* HID Descriptor */
    9,        /* Size of this descriptor in UINT8s. */
    0x21,       /* HID descriptor type. */
    0x00, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    0x22,   /* Dscriptor type. */
    /* Total length of report descriptor. */
    sizeof(ReportDescriptor) & 0x00FF,
    (sizeof(ReportDescriptor) & 0xFF00) >> 8,

    /* EP Descriptor: interrupt in. */
    7,   /* bLength */
    5,  /* bDescriptorType */
    (1 | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    64 & 0x00FF,
    (64 & 0xFF00) >> 8,
    1,     /* bInterval */
		
    /* EP Descriptor: interrupt out. */
    7,   /* bLength */
    5,  /* bDescriptorType */
    (1 | EP_OUTPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    64 & 0x00FF,
    (64 & 0xFF00) >> 8,
    1,     /* bInterval */
};

/*!<USB Language String Descriptor */
uint8_t gu8StringLang[4] =
{
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
uint8_t gu8VendorStringDesc[] =
{
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
uint8_t gu8ProductStringDesc[] =
{
    20,
    DESC_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'M', 0, 'o', 0, 'u', 0, 's', 0, 'e', 0
};


const uint8_t gu8StringSerial[26] =
{
    26,             // bLength
    DESC_STRING,    // bDescriptorType
    'A', 0, '0', 0, '2', 0, '0', 0, '0', 0, '8', 0, '0', 0, '4', 0, '0', 0, '1', 0, '1', 0, '4', 0
};

const uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    gu8StringSerial
};

const S_USBD_INFO_T gsInfo =
{
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    ReportDescriptor
};


