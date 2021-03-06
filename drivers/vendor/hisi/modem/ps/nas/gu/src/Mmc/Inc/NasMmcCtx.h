/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : NasMmcCtx.h
  版 本 号   : 初稿
  作    者   : zhoujun /40661
  生成日期   : 2011年04月22日
  最近修改   :
  功能描述   : NasMmcCtx.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2011年04月22日
    作    者   : zhoujun /40661
    修改内容   : 创建文件

******************************************************************************/
#ifndef _NAS_MMC_CTX_H_
#define _NAS_MMC_CTX_H_

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

#include  "vos.h"
#include  "PsTypeDef.h"
#include  "Nasrrcinterface.h"
#include  "NasOmInterface.h"
#include  "NasOmTrans.h"
#include  "asnasapi.h"
#include  "product_config.h"
#include  "GmmDef.h"
#include  "MM_Def.h"
#include  "GmmStru.h"
#include  "MM_Global.h"
#include  "GmmCasDef.h"
#include  "Nas_Mem.h"
#include  "NasFsm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include  "NasMmcTimerMgmt.h"
#include  "NasMmlCtx.h"
#include  "NasCommDef.h"

#include "MmaMmcInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 全局变量定义
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define NAS_MMC_MAX_STACK_DEPTH                         (4)                     /* 状态机栈的深度 */
#define NAS_MMC_MAX_HIGH_MSG_NUM                        (2)                     /* 缓存的高优先级消息个数 */
#define NAS_MMC_MAX_MID_MSG_NUM                         (4)                     /* 缓存的中优先级消息个数 */
#define NAS_MMC_MAX_LOW_MSG_NUM                         (8)                     /* 缓存的低优先级消息个数 */
#define NAS_MMC_INVALID_MSG_TYPE                        (0xFFFF)                /* 无效的消息类型 */
#define NAS_MMC_MAX_MSG_QUEUE_NUM                       (8)                     /* 最大缓存的个数 */
#define NAS_MMC_MAX_MSG_BUFFER_LEN                      (1600)                  /* 缓存的最大长度 */


#define NAS_MMC_MAX_REG_PLMN_INFO_NUM                   (80)

#define NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST       (410)    /* 搜网列表PLMN个数扩展160个，250+160 */

#define NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST   (60)
#define NAS_MMC_PLMN_SELECTION_LIST_INVALID_INDEX     (0xFFFF)


#define NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM        (RRC_MAX_HIGH_PLMN_NUM/3)  /* 内部搜网消息中携带的高质量PLMN的最大个数 */
#define NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM         (RRC_MAX_LOW_PLMN_NUM/3)   /* 内部搜网消息中携带的低质量PLMN的最大个数 */

#define NAS_MMC_NUM_ZERO                               (0)                      /*数字初始化为0 */

#define NAS_MMC_MAX_SIGN_THRESHOLD                     (5)                      /* 信号变化门限最大值5db*/

#define NAS_MMC_MAX_SIGN_TIMERINTERVAL                 (20)                      /* 信号变化最大时间间隔(s)*/

#define NAS_MMC_UTRAN_SKIP_W_PLMNSEARCH_MASK           (0x0001)                 /* 9234 nv项usSolutionMask字段第0 bit，控制双Modem下通过另一Modem的PLMN信息控制FDD搜网是否跳过的策略是否启动*/
#define NAS_MMC_SUPPORT_NCELL_SEARCH_MASK              (0x0002)                 /* 9234 nv项usSolutionMask字段第1 bit，通过Modem1的GSM上报的L、TDS邻区信息,
                                                                               Modem0不支持GSM的情况下，T/L丢网后，能够根据传递的邻区频点快速搜索到TDS/LTE*/
#define  NAS_MMC_TDD_ARFCN_MAX_NUM                      (9)                     /* TDD频点列表最大个数，用于GAS根据邻区结构给MTC上报频点信息 */
#define  NAS_MMC_LTE_ARFCN_MAX_NUM                      (8)                     /* LTE频点列表最大个数，用于GAS根据邻区结构给MTC上报频点信息 */

#define  NAS_MMC_LTE_CELL_MAX_NUM                       (8)                     /* LTE小区列表最大个数 */


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
/* en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info DPLMN数据,每7个字节代表一个dplmn信息，第1-3个字节为sim卡格式plmn id，
   第4-5字节为支持的接入技术(0x8000为支持w，0x4000为支持lte，0x0080为支持gsm)，
   第6字节为域信息:1(cs域注册成功)；2(ps域注册成功)；3(cs ps均注册成功)
   第7直接为预置标示信息: 1(预置Dplmn), 0(自学习到的DPLMN) */
#define NAS_MMC_DPLMN_NPLMN_NV_INFO_LEN                   (7) /* en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info nv中DPLMN信息总字节数 */
#define NAS_MMC_DPLMN_NPLMN_NV_PRESETING_FLAG_INDEX       (6) /* en_NV_Item_CMCC_Cfg_Dplmn_Nplmn_Info nv中DPLMN信息中预置标示信息位置 */

#define NAS_MMC_MAX_CFG_DPLMN_NUM       (256)            /* DPLMN的最大个数 */
#define NAS_MMC_MAX_CFG_NPLMN_NUM       (256)            /* NPLMN的最大个数 */
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

#define NAS_MMC_MAX_CFG_HPLMN_NUM       (8)              /* HPLMN的最大个数*/


#define NAS_MMC_WCDMA_BAND_NULL                 0x0000
#define NAS_MMC_WCDMA_BAND_I                    0x0001
#define NAS_MMC_WCDMA_BAND_II                   0x0002
#define NAS_MMC_WCDMA_BAND_III                  0x0004
#define NAS_MMC_WCDMA_BAND_IV                   0x0008
#define NAS_MMC_WCDMA_BAND_V                    0x0010
#define NAS_MMC_WCDMA_BAND_VI                   0x0020
#define NAS_MMC_WCDMA_BAND_VII                  0x0040
#define NAS_MMC_WCDMA_BAND_VIII                 0x0080
#define NAS_MMC_WCDMA_BAND_IX                   0x0100

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_MMC_FSM_ID_ENUM_UINT32
 枚举说明  : 状态机ID枚举定义
 1.日    期   : 2011年4月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
enum NAS_MMC_FSM_ID_ENUM
{
    /* NAS MMC L1状态机的名称 */
    NAS_MMC_FSM_L1_MAIN                                     =0X00,

    /* NAS MMC L2状态机的名称,存在多个L2状态机 */

    /* 协议栈初始化L2状态机 */
    NAS_MMC_FSM_SWITCH_ON                                   =0X01,

    /* 协议栈关机L2状态机 */
    NAS_MMC_FSM_POWER_OFF                                   =0X02,

    /* PLMN SELECTION 状态机 */
    NAS_MMC_FSM_PLMN_SELECTION                              =0X03,

    /* ANYCELL搜网状态机 */
    NAS_MMC_FSM_ANYCELL_SEARCH                              =0X04,

    /* 异系统重选状态机 */
    NAS_MMC_FSM_INTER_SYS_CELLRESEL                         =0X05,

    /* 异系统出服务区搜网状态机 */
    NAS_MMC_FSM_INTER_SYS_OOS                               =0X06,

    /* 列表搜网状态机 */
    NAS_MMC_FSM_PLMN_LIST                                   =0X07,

    /* SYSCFG配置L2状态机 */
    NAS_MMC_FSM_SYSCFG                                      =0X08,

    /* BG搜网L2状态机 */
    NAS_MMC_FSM_BG_PLMN_SEARCH                              =0X09,

    /* 异系统Handover状态机 */
    NAS_MMC_FSM_INTER_SYS_HO                                =0X0A,

    /* 异系统CellChange状态机 */
    NAS_MMC_FSM_INTER_SYS_CCO                               =0X0B,

    NAS_FSM_BUTT

};
typedef VOS_UINT32 NAS_MMC_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8
 结构说明  : MMC PLMN搜网类型
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_PLMN_SELECTION_MODE_ENUM
{
    NAS_MMC_PLMN_SELECTION_MODE_AUTO,                                   /* 自动搜网模式 */
    NAS_MMC_PLMN_SELECTION_MODE_MANUAL,                                 /* 手动模式 */
    NAS_MMC_PLMN_SELECTION_MODE_BUTT
};
typedef VOS_UINT8 NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8;


enum NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM
{
    NAS_MMC_SPEC_PLMN_SEARCH_RUNNING,                             /* 正在指定搜网,包含主动释放、指定搜网、主动挂起 */
    NAS_MMC_SPEC_PLMN_SEARCH_STOP,                                /* 没有指定搜网 */
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_BUTT
};
typedef VOS_UINT8 NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8;


enum NAS_MMC_AS_CELL_CAMP_ON_ENUM
{
    NAS_MMC_AS_CELL_CAMP_ON,                             /* 接入层当前驻留状态 */
    NAS_MMC_AS_CELL_NOT_CAMP_ON,                         /* 接入层当前非驻留状态,包含接入层主动发送Not camp on和NAS发送搜网 */
    NAS_MMC_AS_CELL_CAMP_ON_BUTT
};
typedef VOS_UINT8 NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_WAIT_MM_START_CNF_ENUM
 结构说明  : 用于标记收到的MM/GMM的开机回复消息
*****************************************************************************/
enum NAS_MMC_WAIT_MM_START_CNF_ENUM
{
    NAS_MMC_WAIT_MMGMM_START_CNF_NULL   = 0x00,
    NAS_MMC_WAIT_MMCGMM_START_CNF       = 0x01,
    NAS_MMC_WAIT_MMCMM_START_CNF        = 0x02
};
typedef VOS_UINT8 NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_WAIT_AS_START_CNF_ENUM
 结构说明  : 用于标记收到的GU接入层的开机回复消息
*****************************************************************************/
enum NAS_MMC_WAIT_AS_START_CNF_ENUM
{
    NAS_MMC_WAIT_GASWAS_START_CNF_NULL  = 0x00,
    NAS_MMC_WAIT_GAS_START_CNF          = 0x01,
    NAS_MMC_WAIT_WAS_START_CNF          = 0x02
};
typedef VOS_UINT8 NAS_MMC_WAIT_AS_START_CNF_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_MM_POWEROFF_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MMC关机等待MM,GMM的回复标志
*****************************************************************************/
enum    NAS_MMC_MM_POWEROFF_FLAG_ENUM
{
    NAS_MMC_MMGMM_POWER_OFF_NULL_FLG    = 0x00,
    NAS_MMC_MM_POWER_OFF_FLG            = 0x01,
    NAS_MMC_GMM_POWER_OFF_FLG           = 0x02
};

typedef VOS_UINT8 NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_AS_POWEROFF_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MMC关机等待GAS,WAS,LMM的回复标志
*****************************************************************************/
enum    NAS_MMC_AS_POWEROFF_FLAG_ENUM
{
    NAS_MMC_AS_POWER_OFF_NULL_FLG       = 0x00,
    NAS_MMC_GAS_POWER_OFF_FLG           = 0x01,
    NAS_MMC_WAS_POWER_OFF_FLG           = 0x02,
    NAS_MMC_LTE_POWER_OFF_FLG           = 0x04
};

typedef VOS_UINT8 NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_SUSPEND_RSP_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MMC收到挂起消息后，等待MM,GMM的回复标志
*****************************************************************************/
enum    NAS_MMC_SUSPEND_RSP_FLAG_ENUM
{
    NAS_MMC_SUSPEND_RSP_NULL_FLG        = 0x00,
    NAS_MMC_MM_SUSPEND_RSP_FLG          = 0x01,
    NAS_MMC_GMM_SUSPEND_RSP_FLG         = 0x02,
    NAS_MMC_MMGMM_SUSPEND_RSP_FLG       = 0x03,
};
typedef VOS_UINT8 NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8;


/*****************************************************************************
 枚举名    : NAS_MMC_RESUME_RSP_FLAG_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : MMC收到GUL的resume ind消息后，等待MM,GMM的resume回复标志
*****************************************************************************/
enum    NAS_MMC_RESUME_RSP_FLAG_ENUM
{
    NAS_MMC_RESUME_RSP_NULL_FLG         = 0x00,
    NAS_MMC_MM_RESUME_RSP_FLG           = 0x01,
    NAS_MMC_GMM_RESUME_RSP_FLG          = 0x02,
    NAS_MMC_MMGMM_RESUME_RSP_FLG        = 0x03,
};
typedef VOS_UINT8 NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8;

/*RRC signaling status*/
enum NAS_MMC_SIGNALING_EXIST_ENUM
{
    NAS_MMC_SIGNALING_NOT_EXIST                 = (0x00),
    NAS_MMC_PS_SIGNALING_PRESENT                = (0x01),
    NAS_MMC_CS_SIGNALING_PRESENT                = (0x02),
    NAS_MMC_CS_PS_SIGNALING_PRESENT             = (0x03),
    NAS_MMC_RRC_CONNECTION_PRESENT              = (0x04),
    NAS_MMC_EPS_CONNECTION_SIGNALING_PRESENT    = (0x08),
    NAS_MMC_EPS_CONNECTION_DATA_PRESENT         = (0x10),
    NAS_MMC_SIGNALING_EXIST_BUTT
};

/*****************************************************************************
 枚举名    : NAS_MMC_REG_DOMAIN_ENUM_UINT8
 枚举说明  : 注册的域信息
 1.日    期   : 2011年5月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
enum NAS_MMC_REG_DOMAIN_ENUM
{
    NAS_MMC_REG_DOMAIN_NONE  = 0x00,                                            /* 注册结果域为无域 */
    NAS_MMC_REG_DOMAIN_CS    = 0x01,                                            /* 注册结果域为CS域 */
    NAS_MMC_REG_DOMAIN_PS    = 0x02,                                            /* 注册结果域为PS域 */
    NAS_MMC_REG_DOMAIN_PS_CS = 0x03,                                            /* 注册结果域为CS+PS域 */
    NAS_MMC_REG_DOMAIN_EPS   = 0x04,                                            /* 注册结果域为EPS域 */
    NAS_MMC_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_REG_DOMAIN_ENUM_UINT8;


enum NAS_MMC_PLMN_SEARCH_SCENE_ENUM
{
    NAS_MMC_PLMN_SEARCH_SCENE_SWITCH_ON,                        /* 开机 */
    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST,                        /* 出服务区 */
    NAS_MMC_PLMN_SEARCH_SCENE_SYSCFG_SET,                       /* Syscfg设置触发搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED,          /* Available Timer超时触发搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_USER_LIST,                        /* 用户列表搜网结束后触发搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_PLMN_SEARCH,              /* 注册被拒触发正常搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_REJ_CURRENT_PLMN_SEARCH,      /* 注册被拒触发搜当前网络 */
    NAS_MMC_PLMN_SEARCH_SCENE_USER_SPEC_PLMN_SEARCH,            /* 用户指定搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_MANUAL_CHANGE_AUTO_MODE,          /* 手动搜网模式修改为自动模式触发搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,            /* 高优先级搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_DISABLE_LTE,                      /* disable LTE触发搜网 */
    NAS_MMC_PLMN_SEARCH_SCENE_INTER_SYS_OOS,
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_SERVIEC_REJ,                 /* CSFB过程中SERVICE REJECT时导致的搜网场景*/
    NAS_MMC_PLMN_SEARCH_SCENE_USER_AUTO_RESEL,                  /*  用户自动重选  */

    NAS_MMC_PLMN_SEARCH_SCENE_AVAILABLE_TIMER_EXPIRED_NCELL_SEARCH, /* Available Timer超时触发的ncell搜网 */

    NAS_MMC_PLMN_SEARCH_SCENE_RF_ENABLE,                        /* 搜网NO RF失败后，RF可用触发搜网或者周期搜网定时器超时触发搜网 */               

    NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_RAT_HPLMN_SEARCH,       /* 高优先级RAT的HPLMN搜索 */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_NCELL,                        /* 根据NCELL信息进行搜网和注册 */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_HPLMN,                        /* 只搜索和注册(E)HPLMN */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_PREF_PLMN,                    /* 只搜索和注册(E)HPLMN+UPLMN+OPLMN */
    NAS_MMC_PLMN_SEARCH_SCENE_REG_ANY_PLMN,                     /* 可以搜索和注册任何非禁止网络 */


    NAS_MMC_PLMN_SEARCH_SCENE_AREA_LOST_ROAMING_CFG,           /*软银定制漫游状态下丢网的搜网场景*/
    NAS_MMC_PLMN_SEARCH_SCENE_ENABLE_LTE_PLMN_SEARCH,         /* enable lte定时器超时触发搜网的场景 */
    NAS_MMC_PLMN_SEARCH_SCENE_CSFB_ABORT,                     /* 打断CSFB触发的搜网流程触发搜网的场景 */

    NAS_MMC_PLMN_SEARCH_SCENE_BUTT
};
typedef VOS_UINT32 NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32;

/*****************************************************************************
 枚举名    : NAS_MMC_SERVICE_ENUM_UINT8
 枚举说明  : MMC当前的服务状态
 1.日    期   : 2011年7月11日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
enum NAS_MMC_SERVICE_ENUM
{
    NAS_MMC_NORMAL_SERVICE,
    NAS_MMC_LIMITED_SERVICE,
    NAS_MMC_LIMITED_SERVICE_REGION,
    NAS_MMC_NO_SERVICE,
    NAS_MMC_SERVICE_BUTT
};
typedef VOS_UINT8  NAS_MMC_SERVICE_ENUM_UINT8;



/*****************************************************************************
 枚举名    : NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8
 结构说明  : 初始化MMC CTX类型
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_INIT_CTX_TYPE_ENUM
{
    NAS_MMC_INIT_CTX_STARTUP                    = 0,
    NAS_MMC_INIT_CTX_POWEROFF                   = 1,
    NAS_MMC_INIT_CTX_BUTT
};
typedef VOS_UINT32 NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8;





enum NAS_MMC_ADDITIONAL_ACTION_ENUM
{
    NAS_MMC_ADDITIONAL_ACTION_CSPS_ANYCELL                      = 0,            /* 卡无效，任意小区驻留,PS:#3,#6,#8,CS/PS:Auth Fail */
    NAS_MMC_ADDITIONAL_ACTION_PLMN_SELECTION                    = 1,            /* #11,#13需要触发搜网; attempt counter>=Max且有搜网定制*/
    NAS_MMC_ADDITIONAL_ACTION_SEARCH_SUITABLE_CELL_IN_SAME_PLMN = 2,            /* #15 触发搜索当前网络 */
    NAS_MMC_ADDITIONAL_ACTION_CELL_SELECTION                    = 3,            /* #12，不搜网，也不需要继续等待注册，由接入层进行重选 */
    NAS_MMC_ADDITIONAL_ACTION_WAIT_REG_ATTEMPT                  = 4,            /* #other cause, attempt counter<Max值,等待下一次注册尝试 */
    NAS_MMC_ADDITIONAL_ACTION_NORMAL_CAMP_ON                    = 5,            /* CS或PS驻留成功，不需要搜网 */
    NAS_MMC_ADDITIONAL_ACTION_ACCESS_BARRED                     = 6,            /* access barred，不需要搜网 */
    NAS_MMC_ADDITIONAL_ACTION_OPTIONAL_PLMN_SELECTION           = 7,            /* PS #14 可选搜网,依赖CS的注册结果;attempt counter>=Max且无搜网定制*/
    NAS_MMC_ADDITIONAL_ACTION_LIMITED_CAMP_ON                   = 8,            /* 只是CS/PS卡无效，或Gprs not support,
                                                                                   CS only或PS Only时等受限驻留，不需要搜网 */
    NAS_MMC_ADDITIONAL_ACTION_SINGLE_DOMAIN_ANYCELL             = 9,            /* CS和PS分域注册导致的卡无效:CS注册被拒是2,3,6 且PS:7*/
    NAS_MMC_ADDITIONAL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8;
enum NAS_MMC_NET_STATUS_ENUM
{
    NAS_MMC_NET_STATUS_NO_SEARCHED,                     /* 未搜索，当前环境中是否存在该网络还不确定 */
    NAS_MMC_NET_STATUS_SEARCHED_NO_EXIST,               /* 已搜索，当前环境中不存在对应接入技术的网络 */
    NAS_MMC_NET_STATUS_SEARCHED_EXIST,                  /* 已搜索，当前环境中存在对应接入技术的网络，但还未尝试驻留 */
    NAS_MMC_NET_STATUS_SEARCHED_REGISTERED,             /* 已搜索，对应接入技术的网络存在，并且已经尝试过注册 */
    NAS_MMC_NET_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MMC_NET_STATUS_ENUM_UINT8;


enum NAS_MMC_NET_QUALITY_ENUM
{
    NAS_MMC_NET_QUALITY_UNKNOWN,                     /* 网络信号未知 */
    NAS_MMC_NET_HIGH_QUALITY,                        /* 网络信号为高质量 */
    NAS_MMC_NET_LOW_QUALITY,                         /* 网络信号为低质量 */
    NAS_MMC_NET_QUALITY_BUTT
};
typedef VOS_UINT8 NAS_MMC_NET_QUALITY_ENUM_UINT8;
enum NAS_MMC_PLMN_TYPE_ENUM
{
    NAS_MMC_PLMN_TYPE_RPLMN,                     /* 该网络为RPLMN */
    NAS_MMC_PLMN_TYPE_USER_SEPC_PLMN,            /* 该网络为用户指定网络 */
    NAS_MMC_PLMN_TYPE_HPLMN,                     /* 该网络为Home或者EHome PLMN */
    NAS_MMC_PLMN_TYPE_UPLMN,                     /* 该网络为User Controlled PLMN */
    NAS_MMC_PLMN_TYPE_OPLMN,                     /* 该网络为Operator Controlled PLMN */
    NAS_MMC_PLMN_TYPE_EPLMN,                     /* 该网络为等效网络 */
    NAS_MMC_PLMN_TYPE_AVAIL_PLMN,                /* 该网络为其它可用网络 */
    NAS_MMC_PLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_PLMN_TYPE_ENUM_UINT8;
enum NAS_MMC_ROAM_PLMN_TYPE_ENUM
{
    NAS_MMC_ROAM_PLMN_TYPE_FORBIDDEN    = 0,          /* 该网络在禁止网络中 */
    NAS_MMC_ROAM_PLMN_TYPE_NPLMN        = 1,          /* 该网络在NPLMN中 */
    NAS_MMC_ROAM_PLMN_TYPE_AVAIL_PLMN   = 2,          /* 该网络为其它可用网络 */
    NAS_MMC_ROAM_PLMN_TYPE_OPLMN        = 3,          /* 该网络为Operator Controlled PLMN */
    NAS_MMC_ROAM_PLMN_TYPE_UPLMN        = 4,          /* 该网络为User Controlled PLMN */
    NAS_MMC_ROAM_PLMN_TYPE_DPLMN        = 5,          /* 该网络在DPLMN中 */
    NAS_MMC_ROAM_PLMN_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_ROAM_PLMN_TYPE_ENUM_UINT8;



enum NAS_MMC_WAIT_REG_RESULT_IND_ENUM
{
    NAS_MMC_WAIT_REG_RESULT_IND_NULL   = 0x00,                                  /*当前不需要等待CS/PS的注册结果*/
    NAS_MMC_WAIT_REG_RESULT_IND_CS     = 0x01,                                  /*当前需要等待CS的注册结果*/
    NAS_MMC_WAIT_REG_RESULT_IND_PS     = 0x02,                                  /*当前需要等待PS的注册结果*/
    NAS_MMC_WAIT_REG_RESULT_IND_IMS    = 0x04,                                  /*当前需要等待IMS的注册结果*/
    NAS_MMC_WAIT_REG_RESULT_IND_BUTT
};
typedef VOS_UINT8 NAS_MMC_WAIT_REG_RSLT_IND_ENUM_UINT8;


enum NAS_MMC_AT_ACTION_TYPE_ENUM
{
    NAS_MMC_AT_ACTION_TYPE_START_FOREVER                        = 0,            /* 指示WRRC和GRRC永久启动 */
    NAS_MMC_AT_ACTION_TYPE_START_ONCE                           = 1,            /* 指示WRRC和GRRC永久启动一次 */
    NAS_MMC_AT_ACTION_TYPE_STOP                                 = 2,            /* 指示WRRC和GRRC停止 */
    NAS_MMC_AT_ACTION_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_AT_ACTION_TYPE_ENUM_UINT8;
enum NAS_MMC_AT_MSG_TYPE_ENUM
{
    NAS_MMC_AT_MSG_TYPE_CELL_NONE                                   = 0,        /* 表示不获取小区任何信息 */
    NAS_MMC_AT_MSG_TYPE_CELL_SIGN                                   = 1,        /* 表示获取小区信息强度 */
    NAS_MMC_AT_MSG_TYPE_CELL_ID                                     = 2,        /* 表示获取小区ID */
    NAS_MMC_AT_MSG_TYPE_CELL_BLER                                   = 4,        /* 表示获取信道误码率 */
    NAS_MMC_AT_MSG_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_AT_MSG_TYPE_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_ABORT_FSM_TYPE_UINT8
 结构说明  : Abort类型
 1.日    期   : 2011年7月14日
   作    者   : zhoujun 40661
   修改内容   : 新增
*****************************************************************************/
enum NAS_MMC_ABORT_FSM_TYPE
{
    NAS_MMC_ABORT_FSM_IMMEDIATELY           = 0,
    NAS_MMC_ABORT_FSM_DELAY                 = 1,
    NAS_MMC_ABORT_BUTT
};
typedef VOS_UINT8 NAS_MMC_ABORT_FSM_TYPE_UINT8;



enum NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM
{
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_USER_LIST,                                     /* 用户列表搜网结束后出发搜网 */
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_DISABLE_LTE,                                   /* disable LTE触发搜网 */
    NAS_MMC_PLMN_LIST_SEARCH_SCENE_BUTT
};
typedef VOS_UINT8  NAS_MMC_PLMN_LIST_SEARCH_SCENE_ENUM_UINT8;


enum NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM
{
    NAS_MMC_BG_PLMN_SEARCH_SCENE_AREA_LOST,                                     /* 出服务区 */
    NAS_MMC_BG_PLMN_SEARCH_SCENE_DISABLE_LTE,                                   /* disable LTE触发搜网 */
    NAS_MMC_BG_PLMN_SEARCH_SCENE_BUTT
};
typedef VOS_UINT8 NAS_MMC_BG_PLMN_SEARCH_SCENE_ENUM_UINT8;



enum NAS_MMC_COVERAGE_TYPE_ENUM
{
    NAS_MMC_COVERAGE_TYPE_NONE              = 0,                                /* 无网络覆盖 */
    NAS_MMC_COVERAGE_TYPE_LOW               = 1,                                /* 有低质量网络覆盖*/
    NAS_MMC_COVERAGE_TYPE_HIGH              = 2,                                /* 有高质量网络覆盖 */
    NAS_MMC_COVERAGE_TYPE_BUTT
};
typedef VOS_UINT8  NAS_MMC_COVERAGE_TYPE_ENUM_UINT8;
enum NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM
{
    NAS_MMC_CS_DOMAIN_CAPA_NO_CHANGE                        = 0,                /* CS域能力无变化 */
    NAS_MMC_CS_DOMAIN_CAPA_UNAVAIL_TO_AVAIL                 = 1,                /* CS域由不可用到可用 */
    NAS_MMC_CS_DOMAIN_CAPA_AVAIL_TO_UNAVAIL                 = 2,                /* CS域由可用到不可用 */
    NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_CS_DOMAIN_CAPA_CHANGE_TYPE_ENUM_UINT8;
enum NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM
{
    NAS_MMC_STORE_HIGH_PRIO_PLMN_SELECTION_LIST             = 0,                /* 存储的是高优先级搜网列表信息 */
    NAS_MMC_BACKUP_PLMN_SELECTION_LIST                      = 1,                /* 存储的是选网状态机的列表信息的备份 */
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_BUTT                                       /* 当前信息不可用 */
};
typedef VOS_UINT8 NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8;
enum NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM
{
    NAS_MMC_AVAILABLE_TIMER_TYPE_NCELL                      = 0,                /* available定时器启动时类型为ncell搜网 */
    NAS_MMC_AVAILABLE_TIMER_TYPE_NORMAL                     = 1,                /* available定时器启动时类型为普通搜网 */
    NAS_MMC_AVAILABLE_TIMER_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8;


enum NAS_MMC_REG_CONTROL_ENUM
{
    NAS_MMC_REG_CONTROL_BY_3GPP_MMC = 0,                 /* 搜索到网络后，是否注册按目前3GPP协议模块MMC控制 */
    NAS_MMC_REG_CONTROL_BY_3GPP2_CBP,                    /*搜索到网络后，是否注册由3GPP2协议CDMA Baseband Protocol控制 */
    NAS_MMC_REG_CONTROL_BUTT
};
typedef VOS_UINT8 NAS_MMC_REG_CONTROL_ENUM_UINT8;

/*****************************************************************************
 枚举名    : NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8
 结构说明  : DPLMN NPLMN是自学习得到的还是NV预置的
 1.日    期   : 2015年5月18日
   作    者   : c00318887
   修改内容   : 新建
*****************************************************************************/
enum NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM
{
    NAS_MMC_DPLMN_NPLMN_SELF_LEARING_TYPE = 0,           /* DPLMN NPLMN是自学习得到的 */
    NAS_MMC_DPLMN_NPLMN_PRESETTING_TYPE,                 /* DPLMN NPLMN是NV预置的 */
    NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8;

/* Added by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

/*****************************************************************************
 结构名    : NAS_MMC_ENTRY_MSG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 需要保存的入口消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucEntryMsgBuffer[NAS_MMC_MAX_MSG_BUFFER_LEN];
} NAS_MMC_ENTRY_MSG_STRU;



typedef struct
{
    VOS_UINT32                              ulPlmnSearchFlg;                    /* 缓存的搜网存在标志 */
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32   enPlmnSearchScene;                  /* 搜网场景 */
}NAS_MMC_BUFFERED_PLMN_SEARCH_INFO_STRU;



typedef struct{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;         /* 网络的接入技术 */
    NAS_MMC_NET_STATUS_ENUM_UINT8      enNetStatus;       /* 网络的存在状态 */
    NAS_MMC_NET_QUALITY_ENUM_UINT8     enQuality;         /* 网络的信号质量 */
    VOS_UINT8                          ucReserve;
    VOS_INT32                          lRscp;             /* RSCP测量值 */
}NAS_MMC_PLMN_RAT_INFO_STRU;


typedef struct{
    NAS_MML_PLMN_ID_STRU                stPlmnId;                                   /* 此网络的PLMN ID */
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;                                 /* 网络类型        */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           ucRatNum;                                   /* 接入技术信息中有效的接入技术个数        */
    NAS_MMC_PLMN_RAT_INFO_STRU          astPlmnRatInfo[NAS_MML_MAX_RAT_NUM];        /* 此网络各接入技术的信息 */
}NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucSearchAllBand;   /* 是否在当前接入技术执行过全频搜网, VOS_TRUE:执行过全频搜, VOS_FALSE:未执行过 */
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverageType;    /* 当前接入技术下的网络覆盖类型, 0:不存在覆盖，1:存在低质量网络覆盖,2:存在高质量网络覆盖 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;         /* 网络的接入技术 */
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg;

    VOS_UINT8                           ucSearchRplmnAndEplmnFlg;
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag;
    
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-22, begin */
    VOS_UINT8                           ucSearchDplmnAndHplmnFlg;
    VOS_UINT8                           aucReserved[1];
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-22, end */
    
}NAS_MMC_RAT_SEARCH_INFO_STRU;
typedef struct
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsRegCause;                           /* CS注册结果cause值 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsRegCause;                           /* PS注册结果cause值 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsRegAdditionalAction;                /* 当前网络CS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsRegAdditionalAction;                /* 当前网络PS域注册结果的附加处理 */
    VOS_UINT8                           ucWaitRegRsltFlag;                      /* 等待 CS/PS的注册标志 */
    VOS_UINT8                           ucReserve;
}NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU;
typedef struct
{
    VOS_UINT16                             usSearchPlmnNum;                     /* 列表中保存的PLMN个数 */
    VOS_UINT8                              aucReserve[2];
    NAS_MMC_PLMN_SELECTION_PLMN_INFO_STRU  astPlmnSelectionList[NAS_MMC_MAX_PLMN_NUM_IN_SELECTION_LIST]; /* 搜网列表 */
}NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU;


typedef struct
{
    NAS_MML_PLMN_WITH_RAT_STRU          stPlmnWithRat;
    NAS_MMC_PLMN_TYPE_ENUM_UINT8        enPlmnType;
    NAS_MMC_NET_STATUS_ENUM_UINT8       enNetStatus;
    VOS_UINT8                           aucLac[NAS_MML_MAX_LAC_LEN];
}NAS_MMC_ROAM_PLMN_INFO_STRU;


typedef struct
{
    VOS_UINT16                             usSearchPlmnNum;                     /* 列表中保存的PLMN个数 */
    VOS_UINT8                              aucReserve[2];
    NAS_MMC_ROAM_PLMN_INFO_STRU            astPlmnSelectionList[NAS_MMC_MAX_ROAM_PLMN_NUM_IN_SELECTION_LIST]; /* 搜网列表 */
}NAS_MMC_ROAM_PLMN_LIST_INFO_STRU;






typedef struct
{
    VOS_UINT32                          ulCsAttemptCount;                       /* CS注册的尝试次数 */
    VOS_UINT32                          ulPsAttemptCount;                       /* PS注册的尝试次数 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsRegAdditionalAction;               /* 当前网络CS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsRegAdditionalAction;               /* 当前网络PS域注册结果的附加处理 */
    VOS_UINT8                           ucReserve[2];
}NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU;


typedef struct
{
    NAS_MMC_L1_MAIN_REG_RSLT_INFO_STRU                      stRegRsltInfo;                    /* 保存搜网状态机注册结果信息 */
    VOS_UINT32                                              ulCurTimerCount;                  /* 当前Available Timer启动次数 */
    
    VOS_UINT32                                              ulCurHighRatHplmnTimerCount;      /* 当前high prio rat hplmn Timer启动次数 */

    VOS_UINT32                                              ulCurNcellSearchTimerCount;  /* 当前ncell快速搜网启动次数 */

    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType;
    VOS_UINT8                                               aucReserved[3];

}NAS_MMC_FSM_L1_MAIN_CTX_STRU;


typedef struct
{
    VOS_UINT8                                 ucAbortFlg;                       /* 当前状态机标志是否收到终止要求,VOS_TRUE:收到, VOS_FALSE:未收到 */
    VOS_UINT8                                 ucRelRequestFlg;                  /* 是否主动请求连接是否,VOS_TRUE:是主动请求, VOS_FALSE:被动等待释放 */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8           ucInterSysSuspendRat;             /* 记录异系统状态机发起时的接入技术，如等注册结果时从G切换到W */  
    VOS_UINT8                                 aucReserve[1];
    
    NAS_MMC_PLMN_SELECTION_REG_RSLT_INFO_STRU stRegRlstInfo;                    /* 保存选网状态机中注册结果信息 */
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU     stPlmnSelectionListInfo;          /* 保存选网状态机中选网列表信息 */
    NAS_MMC_RAT_SEARCH_INFO_STRU              astSearchRatInfo[NAS_MML_MAX_RAT_NUM];  /* 保存不同接入技术的搜索信息 */
    NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU  stForbRoamLaInfo;
    NAS_MML_PLMN_ID_STRU                      stForbGprsPlmn;                   /* "forbidden PLMNs for GPRS service"  */

    NAS_MML_PLMN_ID_STRU                      stCsPsMode1ReCampLtePlmn;         /* 保存当前L网络的PLMNID */

    NAS_MML_PLMN_WITH_RAT_STRU                stCurrSearchingPlmn;                /* 当前正在尝试的网络及其接入技术,用于at+cops=0 9074 nv项开启打断时判断当前正在搜索的网络是否为hplmn */

    VOS_UINT8                                 ucExistRplmnOrHplmnFlag;        /* 接入层上报的searched plmn info是否存在rplmn和hplmn标识，
                                                                                 如果存在则按非漫游搜网处理，后续即使上报了与rplmn和hplmn不同国家码的网络也不打断*/
}NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU;



typedef struct
{
    VOS_UINT8                       ucTotalSwitchOnRatNum;                         /* 向接入层发送开机请求的总个数 */
    VOS_UINT8                       ucSwitchOnIndex;                            /* 指向需要开机对应模的接入技术的下标 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8 aucSwitchOnRatPrio[NAS_MML_MAX_RAT_NUM];    /* 存放设置开机需要发给接入层的先后顺序 */
    VOS_UINT8                       aucResevel[3];
}NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU;
typedef struct
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8 enSwitchOnAsRat;                            /* 存放设置开机需要发给接入层的接入技术 */
    VOS_UINT8                       ucNeedWaitCnfFlag;                          /* 需要等待该接入模的回复标识 */
    VOS_UINT8                       aucReserve[2];
}NAS_MMC_AS_SWITCH_ON_CNF_INFO_STRU;

typedef struct
{
    VOS_UINT8                           ucMmcMmStartCnfFlg;
    
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulMmcReadSimFileFlg;
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU         stSwitchOnRecord; 

    /* 存放接入层开机回复信息表 */
    NAS_MMC_AS_SWITCH_ON_CNF_INFO_STRU  astSwitchOnCnfInfoList[NAS_MML_MAX_RAT_NUM];           

    /* 开机前NV中保存的IMSI的内容 */
    VOS_UINT8                           aucLastImsi[NAS_MML_MAX_IMSI_LEN];
    VOS_UINT8                           aucReserved[3];
}NAS_MMC_FSM_SWITCH_ON_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucMmcMmPowerOffCnfFlg;                  /* 用于记录是否需要等待MM和GMM的回复消息标志 */
    VOS_UINT8                           ucMmcAsPowerOffCnfFlg;                  /* 用于记录是否需要等待接入层:WAS/GAS/LMM的回复消息标志 */

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat;                        /* 关机时记录的当前的主模 */    
    VOS_UINT8                           aucReserve[1];
    NAS_MML_PLMN_RAT_PRIO_STRU          stSlaveModeList;
}NAS_MMC_FSM_POWER_OFF_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU
 结构说明  : Anycell搜网控制结构
*****************************************************************************/
typedef struct
{
    NAS_MML_PLMN_RAT_PRIO_STRU          stMmcPlmnRatPrio;
    VOS_UINT8                           aucSearchedFlag[NAS_MML_MAX_RAT_NUM];   /* 标识是否搜索过的接入技术:VOS_TRUE 表搜过，VOS_FALSE 表未搜过 */
    VOS_UINT8                           ucAbortFlag;                            /* Abort消息存在标志:VOS_TRUE表示存在,VOS_FALSE表示不存在 */
}NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU;


typedef struct
{
    VOS_UINT8                          ucMmcSuspendRspFlg;                      /* MMC挂起回复的标志 */
    VOS_UINT8                          ucMmcResumeRspFlg;                       /* MMC恢复回复的标志 */
    VOS_UINT8                          ucAbortFlg;                              /* 是否终止状态机标志,VOS_TRUE:表示收到状态机的打断消息;VOS_FALSE:表示未收到状态机的打断消息 */
    VOS_UINT8                          ucSndSuspendRelReqFlg;

    MMC_RESUME_ORIGEN_ENUM_UINT8       enResumeOrign;
    VOS_UINT8                          aucReserve[3];

}NAS_MMC_FSM_INTER_SYS_CELLRESEL_CTX_STRU;
typedef struct
{
    VOS_UINT8                          ucMmcSuspendRspFlg;                      /* MMC挂起回复的标志 */
    VOS_UINT8                          ucMmcResumeRspFlg;                       /* MMC恢复回复的标志 */
    VOS_UINT8                          aucReserve[2];
}NAS_MMC_FSM_INTER_SYS_OOS_CTX_STRU;


typedef struct
{
    VOS_UINT8                           ucMmcSuspendRspFlg;                     /* MMC挂起回复的标志 */
    VOS_UINT8                           ucMmcResumeRspFlg;                      /* MMC恢复回复的标志 */
    VOS_UINT8                           ucCsSigExistFlg;                        /* 切换时存在CS信令连接 */    
    VOS_UINT8                           ucPsSigExistFlg;                        /* 切换时存在PS信令连接 */
}NAS_MMC_FSM_INTER_SYS_HO_CTX_STRU;



typedef struct
{
    VOS_UINT8                           ucMmcSuspendRspFlg;                     /* MMC挂起回复的标志 */
    VOS_UINT8                           ucMmcResumeRspFlg;                      /* MMC恢复回复的标志 */
    VOS_UINT8                           aucReserve[2];
}NAS_MMC_FSM_INTER_SYS_CCO_CTX_STRU;


/*****************************************************************************
 结构名称: NAS_MMC_LOW_PLMN_INFO_STRU
 结构说明: 低质量PLMN信息结构体
 1.日    期   : 2011年7月11日
   作    者   : sunxibo 46746
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_MML_PLMN_ID_STRU                stPlmnId;           /* PLMN ID    */
    VOS_INT32                           lRscp;              /* RSCP测量值 */
}NAS_MMC_LOW_PLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucSearchedFlag;                         /* 标识是否搜索过的接入技术 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;                                  /* 需要搜索的接入技术 */
    VOS_UINT8                           aucResevel[2];
}NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU;


typedef struct
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;                                                  /* 网络的接入技术 */
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType;                                                /* 当前接入技术下的覆盖类型 */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulHighPlmnNum;                                              /* 高质量PLMN的个数 */
    NAS_MML_PLMN_ID_STRU                astHighPlmnList[NAS_MMC_INTRA_MAX_HIGH_QUALITY_PLMN_NUM];   /* 高质量PLMN列表   */
    VOS_UINT32                          ulLowPlmnNum;                                               /* 低质量PLMN的个数 */
    NAS_MMC_LOW_PLMN_INFO_STRU          astLowPlmnList[NAS_MMC_INTRA_MAX_LOW_QUALITY_PLMN_NUM];     /* 低质量PLMN列表   */
}NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucWaitRegRsltFlag;                       /* 等待 CS/PS的注册标志 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enCsRegAdditionalAction;                 /* 当前网络CS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8                    enPsRegAdditionalAction;                 /* 当前网络PS域注册结果的附加处理 */
    VOS_UINT8                                               aucReserve[1];
}NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU;
typedef struct
{
    NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU                      astPlmnListCtrlInfo[NAS_MML_MAX_RAT_NUM];/* LIST搜网的搜索控制信息*/
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                    astPlmnSearchInfo[NAS_MML_MAX_RAT_NUM];  /* LIST搜网过程中搜到的网络列表信息 */
    NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU                    stRegRsltInfo;                           /* LIST搜网等待注册结果以及等待链路释放时收到的注册结果信息 */
    VOS_UINT8                                               ucAbortFlg;                              /* 是否终止状态机标志,VOS_TRUE:表示收到状态机的打断消息;VOS_FALSE:表示未收到状态机的打断消息 */
    VOS_UINT8                                               ucNotifyMmaFlg;                          /* 是否向MMA通知结果,VOT_TRUE:表示MMA定时器超时中止LIST搜网;VOT_FALSE:表示未收到MMA定时器超时的ABORT消息*/

    VOS_UINT8                                               ucPreLteDisableFlg;               /* 发起BG搜索时L是否已经disable态，以区分List搜过程中触发disable LTE的场景，
                                                                                                List搜过程disable lte退出状态机时需要带disable的搜网场景,VOS_TRUE:发起List
                                                                                                搜时L已经disable；VOS_FALSE:发起List搜时L未disable*/

    VOS_UINT8                                               ucAnyCellSrchFlg;               /* LIST搜网之前卡无效,结束后是否需要进行anycell搜网,如果已经做过anycell搜网,
                                                                                               结束不需要重复进行anycell搜网.VOS_TRUE:LIST搜网结束需要进行anycell搜网
                                                                                               VOS_FALSE:LIST搜网结束不需要anycell搜网 */
}NAS_MMC_FSM_PLMN_LIST_CTX_STRU;



typedef struct
{
    VOS_UINT8                       ucSetCurrSyscfgIndex;                       /* 指向需要设置SYSCFG所对应模的接入技术的下标 */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8 aucSyscfgRatPrio[NAS_MML_MAX_RAT_NUM];      /* 存放SYSCFG设置需要发给接入层的先后顺序 */
    VOS_UINT8                       ucTotalSyscfgNum;                           /* 向接入层设置SYSCFG的总个数 */
    VOS_UINT8                       aucResevel[3];

}NAS_MMC_SYSCFG_SETTING_CTRL_STRU;
typedef struct
{
    VOS_UINT8                           ucRelRequestFlg;                  /* 是否主动请求连接是否,VOS_TRUE:是主动请求, VOS_FALSE:被动等待释放 */
    VOS_UINT8                           aucReserve[3];

    VOS_UINT32                          ulNeedSearchPlmnFlag;                   /* syscfg设置是否需要搜网标识 */
    NAS_MMC_SYSCFG_SETTING_CTRL_STRU    stSyscfgSettingRecord;                  /* 记录给接入层下发SYSCFG设置的先后顺序以及当前正在设置的接入层 */

    NAS_MML_PLMN_RAT_PRIO_STRU          stPrePrioRatList;                       /* 进syscfg状态机前的接入技术和优先级 */
}NAS_MMC_FSM_SYSCFG_CTX_STRU;


typedef struct
{
    VOS_UINT8                                 ucRelRequestFlg;                  /* 是否主动请求连接标志,VOS_TRUE:是主动请求, VOS_FALSE:被动等待释放 */
    VOS_UINT8                                 ucWaitRegRsltFlag;                /* 等待 CS/PS的注册标志 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8      enCsRegAdditionalAction;          /* 当前网络CS域注册结果的附加处理 */
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8      enPsRegAdditionalAction;          /* 当前网络PS域注册结果的附加处理 */
}NAS_MMC_BG_PLMN_SEARCH_REG_INFO_STRU;


typedef struct
{
    VOS_UINT32                                ulAbortEventType;                 /* 打断事件ID */

    NAS_MMC_ABORT_FSM_TYPE_UINT8              enAbortType;                      /* 如果接收到终止请求,记录终止的类型 */

    VOS_UINT8                                 ucNeedSndSysInfo;                 /* 是否需要立即给MMA上报系统消息 */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                                 ucPreLteDisableFlg;               /* 发起BG搜索时L是否已经disable态，已区分BG搜过程中触发disable LTE的场景，
                                                                                   BG搜过程disable lte退出状态机时需要带disable的搜网场景,VOS_TRUE:发起BG
                                                                                   搜时L已经disable；VOS_FALSE:发起BG搜时L未disable*/
    VOS_UINT8                                 ucNeedEnableLteFlg;               /* 用于判断在快速指定搜时是否需要enable LTE */
#else
    VOS_UINT8                                 aucReserve[2];
#endif
    NAS_MMC_BG_PLMN_SEARCH_REG_INFO_STRU      stCurHighPrioPlmnRegInfo;         /* 保存状态机中注册过程相关信息 */
    NAS_MML_PLMN_WITH_RAT_STRU                stCurHighPrioPlmn;                /* 当前正在尝试的高优先级网络及其接入技术,用于快速指定搜索失败后，更新该网络状态 */
    NAS_MML_PLMN_WITH_RAT_STRU                stPreCampPlmn;                    /* 发起BG搜索时驻留的PLMN或BG状态机中注册完成后的PLMN及其接入技术 */
    NAS_MML_EQUPLMN_INFO_STRU                 stPreEquPlmnInfo;                 /* 发起BG搜索时或BG状态机中注册完成后的所对应的EQUPLMN信息 */
}NAS_MMC_FSM_BG_PLMN_SEARCH_CTX_STRU;
typedef union
{
    NAS_MMC_FSM_SWITCH_ON_CTX_STRU                      stSwitchOnCtx;
    NAS_MMC_FSM_POWER_OFF_CTX_STRU                      stPowerOffCtx;
    NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU                 stAnyCellSearchCtx;
    NAS_MMC_FSM_PLMN_SELECTION_CTX_STRU                 stPlmnSelectionCtx;

    NAS_MMC_FSM_L1_MAIN_CTX_STRU                        stL1MainCtx;
    NAS_MMC_FSM_INTER_SYS_OOS_CTX_STRU                  stInterSysOosCtx;
    NAS_MMC_FSM_INTER_SYS_CELLRESEL_CTX_STRU            stInterSysCellReselCtx;
    NAS_MMC_FSM_INTER_SYS_HO_CTX_STRU                   stInterSysHoCtx;
    NAS_MMC_FSM_INTER_SYS_CCO_CTX_STRU                  stInterSysCcoCtx;

    NAS_MMC_FSM_SYSCFG_CTX_STRU                         stSyscfgCtx;

    NAS_MMC_FSM_BG_PLMN_SEARCH_CTX_STRU                 stBgPlmnSearchCtx;

    NAS_MMC_FSM_PLMN_LIST_CTX_STRU                      stPlmnListCtx;
}NAS_MMC_FSM_EXTRA_CTX_UNION;


typedef struct
{
    /* 状态机描述指针,指针为NULL表示当前状态机无效  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* 当前状态机标识 */
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId;

    /* 上层状态机标识 */
    NAS_MMC_FSM_ID_ENUM_UINT32          enParentFsmId;

    /* 上层状态机入口消息类型 */
    VOS_UINT32                          ulParentEventType;

    
    /* 上层状态机数据内容栈地址 */
    NAS_MMC_FSM_EXTRA_CTX_UNION        *punParentFsmCtx;

    /* 当前状态 */
    VOS_UINT32                          ulState;                                /* L1状态 */

    /* 入口消息MSGID和内容  */
    NAS_MMC_ENTRY_MSG_STRU              stEntryMsg;

    /* 状态机数据 */
    NAS_MMC_FSM_EXTRA_CTX_UNION         unFsmCtx;
}NAS_MMC_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_FSM_STACK_STRU
 结构说明  : 状态机栈描述结构
 1.日    期   : 2011年5月28日
   作    者   : zhoujun 40661
   修改内容   : 新建

 2.日    期   : 2011年10月9日
   作    者   : zhoujun /40661
   修改内容   : 增加栈POP的标志位
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* 当前压栈的状态机数 */
    VOS_UINT16                          usStackPopFlg;                          /* 当前栈pop标志 */
    NAS_MMC_FSM_CTX_STRU                astFsmStack[NAS_MMC_MAX_STACK_DEPTH];   /* 状态机栈的深度 */
}NAS_MMC_FSM_STACK_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_CACH_MSG_INFO_STRU
 结构说明  : 缓存的消息内容
 1.日    期   : 2011年5月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_MMC_ENTRY_MSG_STRU              stMsgEntry;     /* 缓存的具体内容 */
}NAS_MMC_CACH_MSG_INFO_STRU;


/*****************************************************************************
 结构名    : NAS_MMC_CACH_MSG_INFO_STRU
 结构说明  : 缓存的消息队列
 1.日    期   : 2011年5月28日
   作    者   : zhoujun 40661
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ucCurrIndex;                            /* 记录当前处理缓存的index */
    VOS_UINT8                           ucCacheMsgNum;                          /* 缓存消息的个数 */
    VOS_UINT8                           aucReserve[3];
    NAS_MMC_CACH_MSG_INFO_STRU          astMsgQueue[NAS_MMC_MAX_MSG_QUEUE_NUM]; /* MMC的消息队列数组，存储的是带通用消息头的消息 */
}NAS_MMC_MSG_QUEUE_STRU;
typedef struct
{
    NAS_MML_PROC_TYPE_ENUM_U32          enProcType;         /* 当前的业务过程 */
    NAS_MML_REG_RESULT_ENUM_UINT8       enRegRst;           /* 该过程的处理结果 */
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enReqDomain;        /* 该过程的发起域 */
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enRstDomain;        /* 该过程的结果域 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCnCause;          /* 过程的cause值，失败时为对应原因值，成功时，为NULL */
    VOS_UINT32                          ulAttemptCount;     /* 当前过程的尝试次数 */

}NAS_MMC_GU_ACTION_RSLT_INFO_STRU;


typedef struct
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enRatType;                      /* 网络模式 */
    VOS_UINT8                                   ucSimPsRegStatus;               /* 卡状态，VOS_TRUE表示卡有效，VOS_FALSE表示卡无效 */
    VOS_UINT8                                   aucReserved[2];
}NAS_MMC_SRV_STA_CHNG_INFO_STRU;



typedef struct
{    
    VOS_UINT8                           ucPlmnSrchNoRfFlg;                      /* 当前是否因NO RF导致的搜网失败，接入层上报NO RF则设置为VOS_TRUE,MMC发起搜网时则设置为VOS_FALSE */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;                              /* 上报NO RF时候的接入技术 */
    VOS_UINT8                           aucReserved[2]; 
}NAS_MMC_PLMN_SEARCH_NO_RF_INFO_STRU;



typedef struct
{
    VOS_UINT8                                   ucUtranSkipWPlmnSearchFlag;

    VOS_UINT8                                   ucNcellSearchFlag;              /* 是否支持ncell搜索标识，1:支持；0:不支持；
                                                                                 通过Modem1的GSM上报的L、TDS邻区信息, Modem0不支持GSM的情况下，
                                                                                 T/L丢网后，能够根据传递的邻区频点快速搜索到TDS/LTE;
                                                                                 如果Modem1传递过来的邻区信息不存在的情况下，也能通过历史频点支持NCELL搜索*/
    VOS_UINT8                                   ucNcellSearchFirstTimerLen;     /* 第一阶段邻区频点快速搜索策略的时间间隔 （单位秒）*/
    VOS_UINT8                                   ucNcellSearchSecondTimerLen;    /* 第二阶段邻区频点快速搜索策略的时间间隔 （单位秒）*/
}NAS_MMC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucTdsArfcnNum;                              /* 0表示TDD频点不存在 */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          ausTdsArfcnList[NAS_MMC_TDD_ARFCN_MAX_NUM];
}NAS_MMC_TDS_NCELL_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucLteArfcnNum;                              /* 0表示LTE频点不存在 */
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          ausLteArfcnList[NAS_MMC_LTE_ARFCN_MAX_NUM];

    VOS_UINT8                           ucLteCellNum;                              /* 0表示LTE消息ID不存在 */
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT16                          ausLteCellList[NAS_MMC_LTE_CELL_MAX_NUM];

}NAS_MMC_LTE_NCELL_INFO_STRU;



typedef struct
{
    NAS_MMC_TDS_NCELL_INFO_STRU         stTdsNcellInfo;
    NAS_MMC_LTE_NCELL_INFO_STRU         stLteNcellInfo;
    NAS_MML_EQUPLMN_INFO_STRU           stOtherModemEplmnInfo;
}NAS_MMC_NCELL_SEARCH_INFO_STRU;




typedef struct
{
    NAS_MML_SIM_PLMN_WITH_RAT_STRU                stSimPlmnWithRat;
    NAS_MMC_REG_DOMAIN_ENUM_UINT8                 enRegDomain;
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, begin */
    NAS_MMC_DPLMN_NPLMN_SETTING_TYPE_ENUM_UINT8   enType;
    VOS_UINT8                                     aucReserved[2];
    /* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-20, end */
}NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU;


typedef struct
{
    VOS_UINT8                               ucActiveFlg;                                               /* 定制项使能标志 */
    VOS_UINT8                               ucCMCCHplmnNum;
    NAS_MML_PLMN_ID_STRU                    astCMCCHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                               ucUNICOMHplmnNum;
    NAS_MML_PLMN_ID_STRU                    astUNICOMHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT8                               ucCTHplmnNum;
    NAS_MML_PLMN_ID_STRU                    astCTHplmnList[NAS_MMC_NVIM_MAX_CFG_HPLMN_NUM];
    VOS_UINT16                              usDplmnListNum;                                       /* 本地配置的Dplmn的个数 */
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU   astDPlmnList[NAS_MMC_MAX_CFG_DPLMN_NUM];
    VOS_UINT16                              usNplmnListNum;                                       /* 本地配置的Nplmn的个数 */
    NAS_MMC_SIM_PLMN_WITH_REG_DOMAIN_STRU   astNPlmnList[NAS_MMC_MAX_CFG_NPLMN_NUM];
}NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU;


typedef struct
{
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8        enSelectionMode;              /* MMC当前搜网模式,自动模式或手动模式*/
    VOS_UINT8                                     ucWrrLimitServiceInd;         /* 收到WRR的进入限制服务指示,VOS_FALSE:未收到,VOS_TRUE:收到 */

    NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8            enAsCellCampOn;               /* 接入层是否Camp On */
    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8     enSpecPlmnSearchState;        /* NAS是否为非驻留搜网状态 */

    /*  用户手动指定网络的注册状态,VOS_FALSE:未注册成功,VOS_TRUE:已注册成功
        用户手动指定网络的注册状态的维护:
     1. 在收到用户指定搜的处理入口处 清除该标志;
     2. 向用户上报指定搜网成功的地方 设置该标志, 后续搜网时会搜RPLMN及其EPLMN;
     3. PS注册成功, CS注册失败, 原因为11 12 13 15的情况, 需要清除该标志.
        因为此时CS的RPLMN没有更新为用户指定的PLMN, 此后丢网等触发的搜网不能搜
        RPLMN及其EPLMN, 故需要清除该标志.
        CS注册成功, PS注册失败时, 虽然RPLMN和用户指定PLMN相同, 但为了处理对称,
        也做清除标志的处理. */
    VOS_UINT8                                     ucUserSpecPlmnRegStatus;

    NAS_MMC_REG_CONTROL_ENUM_UINT8                enRegCtrl;
    VOS_UINT8                                     ucAsAnyCampOn;

    VOS_UINT8                                     ucEnableLteTimerExpireFlag; /* 标识enable lte定时器是否超时标识，0:enable lte定时器未超时；1:enable lte定时器超时*/
    NAS_MML_PLMN_ID_STRU                          stDisabledLtePlmnId;    /* 记录驻留LTE下disable lte时驻留的网络信息 */

    NAS_MMC_BUFFERED_PLMN_SEARCH_INFO_STRU        stBufferedPlmnSearchInfo;     /* 记录缓存的搜网标志以及搜网场景信息 */

    NAS_MMC_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU    stDsdaPlmnSearchEnhancedCfg;

    NAS_MML_PLMN_ID_STRU                          stOtherModemPlmnId;           /* 副卡驻留plmn id信息，全f为无效值 */

    NAS_MMC_NCELL_SEARCH_INFO_STRU                stNcellSearchInfo;

    NAS_MML_PLMN_WITH_RAT_STRU                    stUserSpecPlmnId;             /* 用户手动搜网时网络的PLMNID和接入技术 */
    NAS_MML_PLMN_WITH_RAT_STRU                    stUserReselPlmnId;            /* 指定搜网前驻留的PLMNID和接入技术,但同时指定搜网注册成功后也会更新该值 */

    NAS_MMC_SRV_STA_CHNG_INFO_STRU                stLastSrvStaInfo;             /* 上次通知其他模块当前网络模式和卡状态的记录 */

    NAS_MMC_PLMN_SEARCH_NO_RF_INFO_STRU           stPlmnSrchNoRfInfo;
    NAS_MML_PLMN_ID_STRU                                    stLastCampedPlmnId;                      /*存储丢网时上次驻留的PLMN*/

    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                       stDplmnNplmnInfo;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucRatChgForLteOos2GPrefPlmnSelFlg;
    VOS_UINT8                           ucReserve[3];
#endif

}NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU;


typedef struct
{
    NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU                   stHighPrioPlmnSearchListInfo; /* 记录高优先级搜网列表信息(HPLMN+UPLMN+OPLMN支持的接入技术及网络状态)*/
    VOS_UINT8                                               ucFirstStartHPlmnTimerFlg;    /* 记录是否为首次启动HPLMN定时器:VOS_TRUE:首次启动HPLMN定时器；VOS_FALSE:非首次启动HPLMN定时器 */
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enPlmnSelectionListType; 
    VOS_UINT8                                               ucTdHighRatSearchCount;
    VOS_UINT8                                               aucReserve[1];
}NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU;



typedef struct
{
    MMA_MMC_NET_SCAN_REQ_STRU          stNetScanReq;
}NAS_MMC_NET_SCAN_REQ_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_HPLMN_REG_REJ_STRU
 结构说明  : HPLMN被拒的位置区,路由区以及服务域,主要为Plmn not allow的原因值hplmn需要特殊处理
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          aucLac[NAS_MML_MAX_LAC_LEN];/* 位置区 */
    VOS_UINT8                           ucRac;                      /* 路由区 */
    VOS_UINT8                           ucRegRejCnDomain;           /* 被拒绝的服务域 NAS_MMC_REG_DOMAIN_ENUM_UINT8*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRejCause;                 /* 被拒绝的原因值 */
    NAS_MML_PLMN_ID_STRU                stHplmnId;                  /* 被拒绝的PLMN ID */
}NAS_MMC_HPLMN_REG_REJ_STRU;
typedef struct{
    NAS_MML_PLMN_ID_STRU                   stPlmnId;
    VOS_UINT16                             aucLac[NAS_MML_MAX_LAC_LEN];         /* 位置区 */
    VOS_UINT8                              ucRac;                               /* 路由区 */
    VOS_UINT8                              ucReserved;
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enWPsRegStatus;                      /* W网络的注册状态，初始化和注册成功时为NULL */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enWCsRegStatus;                      /* W网络的注册状态，初始化和注册成功时为NULL */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enGPsRegStatus;                      /* G网络的注册状态，初始化和注册成功时为NULL */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enGCsRegStatus;                      /* G网络的注册状态，初始化和注册成功时为NULL */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enLCsRegStatus;                         /* L网络的注册状态，初始化为NULL */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16     enLPsRegStatus;                         /* L网络的注册状态，初始化为NULL */
#endif
}NAS_MMC_PLMN_REG_INFO_STRU;                     /*  对应网络的注册信息           */

typedef struct
{
    VOS_UINT8                               ucPlmnRegInfoNum;                   /* 当前在注册原因列表中 存在的 Plmn个数 */
    VOS_UINT8                               aucReserve[3];
    NAS_MMC_PLMN_REG_INFO_STRU              astPlmnRegInfoList[NAS_MMC_MAX_REG_PLMN_INFO_NUM]; /*本次开机后, Plmn的注册信息 */
}NAS_MMC_PLMN_REG_REJ_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MMC_SERVICE_INFO_CTX_STRU
 结构说明  : NAS MMC 当前的服务状态
 1.日    期   : 2011年6月30日
   作    者   : zhoujun 40661
   修改内容   : 新增
*****************************************************************************/
typedef struct
{
    NAS_MMC_SERVICE_ENUM_UINT8          enCsCurrService;                        /* 当前CS域的服务状态 */
    NAS_MMC_SERVICE_ENUM_UINT8          enPsCurrService;                        /* 当前PS域的服务状态 */
    VOS_UINT8                           aucReserve[2];
}NAS_MMC_SERVICE_INFO_CTX_STRU;


typedef struct
{
    VOS_UINT8                                               ucGcfCh9_4_3_AND_Ch26_7_4_3;            /* GCF的桩变量是否生效,VOS_FALSE:不生效,VOS_TRUE:生效 */
    NAS_MMC_AT_ACTION_TYPE_ENUM_UINT8                       ucActionType;       /* GU接入层主动上报消息的 enActionType的取值 */
    NAS_MMC_AT_MSG_TYPE_ENUM_UINT8                          ucMsgType;          /* GU接入层主动上报消息的 enMsgType的取值 */

    VOS_UINT8                                               ucSignThreshold;
    VOS_UINT8                                               ucMinRptTimerInterval;     /* 间隔上报的时间   */
    VOS_UINT8                                               aucReserve[3];
}NAS_MMC_MAINTAIN_CTX_STRU;





typedef struct
{
    /**************************************************************************
                        NAS MMC状态机状态及其状态栈
    **************************************************************************/
    NAS_MMC_FSM_CTX_STRU                stCurFsm;                               /* 状态机当前的状态机数组 */
    NAS_MMC_FSM_STACK_STRU              stFsmStack;                             /* 状态机的状态机栈数组   */

    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   stPlmnSearchCtrl;                       /* PLMN搜网控制上下文 */
    NAS_MMC_PLMN_REG_REJ_CTX_STRU       stPlmnRegInfo;                          /* PLMN注册结果及其失败原因值上下文 */
    NAS_MMC_SERVICE_INFO_CTX_STRU       stServiceInfo;                          /* MMC当前的服务状态 */
    NAS_MMC_MAINTAIN_CTX_STRU           stMaintainInfo;                         /* 可维可测上下文 */
    NAS_MMC_TIMER_CTX_STRU              astMmcTimerCtx[NAS_MMC_MAX_TIMER_NUM];  /* MMC当前正在运行的定时器资源 */

    NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU   stHighPrioPlmnSearchCtrl;     /* 高优先级搜网控制上下文 */

    NAS_MMC_NET_SCAN_REQ_CTX_STRU       stNetScanReqCtx;

    /**************************************************************************
                        NAS MMC缓存消息队列
    **************************************************************************/
    NAS_MMC_MSG_QUEUE_STRU              stBufferEntryMsgQueue;

}NAS_MMC_CONTEXT_STRU;

extern NAS_MMC_CONTEXT_STRU                    g_stNasMmcCtx;

#if (FEATURE_ON == FEATURE_LTE)
#ifdef WIN32
extern TAF_PLMN_ID_STRU                        g_stSetRplmn;
#endif
#endif
/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/



/*****************************************************************************
  10 函数声明
*****************************************************************************/
VOS_VOID NAS_MMC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_FSM_InitFsmL2(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
);
VOS_VOID NAS_MMC_FSM_QuitFsmL2( VOS_VOID );

VOS_VOID  NAS_MMC_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
);


VOS_UINT32 NAS_MMC_GetFsmTopState( VOS_VOID );

VOS_UINT16  NAS_MMC_GetFsmStackDepth( VOS_VOID );

NAS_MMC_TIMER_CTX_STRU*  NAS_MMC_GetTimerAddr( VOS_VOID );

VOS_UINT32  NAS_MMC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg
);


VOS_UINT32  NAS_MMC_GetNextCachedMsg(
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg
);

VOS_UINT32  NAS_MMC_ClearCacheMsg(
    VOS_UINT32                          ulEventType
);

VOS_UINT32  NAS_MMC_ClearAllCacheMsg( VOS_VOID );

VOS_UINT32  NAS_MMC_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
);


VOS_VOID  NAS_MMC_InitFsmCtx_L1Main(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_SwitchOn(VOS_VOID);

NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU* NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn(VOS_VOID);
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSendingRat_SwitchOn(VOS_VOID);
VOS_VOID NAS_MMC_AddSwitchOnIndex_SwitchOn(VOS_VOID);
VOS_VOID NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn(VOS_VOID);

VOS_UINT8* NAS_MMC_GetLastImsi_SwitchOn(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_PowerOff(VOS_VOID);


VOS_VOID  NAS_MMC_InitFsmCtx_PlmnSelection(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_BgPlmnSearch(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_AnyCellSearch(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCellResel(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysHo(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysCco(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_InterSysOos(VOS_VOID);

VOS_VOID  NAS_MMC_InitFsmCtx_PlmnList(VOS_VOID);


VOS_VOID  NAS_MMC_InitFsmStackCtx(
    NAS_MMC_FSM_STACK_STRU              *pstFsmStack
);

VOS_VOID  NAS_MMC_InitInternalBuffer(
    NAS_MMC_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
);

VOS_VOID NAS_MMC_InitNetScanReqCtx(
    NAS_MMC_NET_SCAN_REQ_CTX_STRU      *pstNetScanReqCtx
);

VOS_VOID  NAS_MMC_InitCurrFsmCtx(
    NAS_MMC_FSM_CTX_STRU                *pstCurrFsmCtx
);

VOS_VOID  NAS_MMC_InitPlmnSearchCtrlCtx(
    NAS_MMC_INIT_CTX_TYPE_ENUM_UINT8     enInitType,
    NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU   *pstPlmnSearchCtrl
);

VOS_VOID  NAS_MMC_InitServiceInfo(
    NAS_MMC_SERVICE_INFO_CTX_STRU       *pstServiceInfo
);


VOS_VOID  NAS_MMC_InitPlmnRegRejCtx(
    NAS_MMC_PLMN_REG_REJ_CTX_STRU           *pstPlmnRegRejInfo
);

VOS_VOID  NAS_MMC_InitMaintainCtx(
    NAS_MMC_MAINTAIN_CTX_STRU           *pstMaintainInfo
);
NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserSpecPlmnId(VOS_VOID);

VOS_UINT32 NAS_MMC_GetUserSpecPlmnRegisterStatus(VOS_VOID);

NAS_MML_PLMN_WITH_RAT_STRU *NAS_MMC_GetUserReselPlmnId(VOS_VOID);

VOS_VOID NAS_MMC_SetUserReselPlmnId(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_SetUserSpecPlmnRegisterStatus(
    VOS_UINT8                           ucRegisterStatus
);

VOS_VOID NAS_MMC_SetUserSpecPlmnId(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnInfo
);

NAS_MML_PLMN_ID_STRU* NAS_MMC_GetLastCampedPlmnid( VOS_VOID );
VOS_UINT32 NAS_MMC_SaveLastCampedPlmnid( 
    VOS_UINT32                   ulMcc,
    VOS_UINT32                   ulMnc
);

NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionMode(VOS_VOID);

VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8      enSelectionMode
);

NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8 NAS_MMC_GetAsCellCampOn(VOS_VOID);

VOS_VOID NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON_ENUM_UINT8   enAsCellCampOn);

NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 NAS_MMC_GetSpecPlmnSearchState(VOS_VOID);

VOS_VOID NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8 enSpecPlmnSearchState);

NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrEntryMsg(VOS_VOID);

NAS_MMC_PLMN_SEARCH_CTRL_CTX_STRU *NAS_MMC_GetPlmnSearchCtrl(VOS_VOID);

NAS_MMC_PLMN_REG_REJ_CTX_STRU *NAS_MMC_GetPlmnRegRejInfo(VOS_VOID);

NAS_MMC_SERVICE_INFO_CTX_STRU *NAS_MMC_GetServiceInfo(VOS_VOID);

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrCsService(VOS_VOID);
NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCurrPsService(VOS_VOID);

NAS_MMC_MAINTAIN_CTX_STRU *NAS_MMC_GetMaintainInfo(VOS_VOID);

VOS_UINT32 NAS_MMC_IsCsNormalService( VOS_VOID );

VOS_UINT32 NAS_MMC_IsPsNormalService( VOS_VOID );

VOS_UINT32  NAS_MMC_IsInValidCampPlmn( VOS_VOID );

VOS_UINT32 NAS_MMC_IsNormalServiceStatus(VOS_VOID);

NAS_MMC_SERVICE_ENUM_UINT8  NAS_MMC_ConverMmStatusToMmc(
    NAS_MMC_REG_DOMAIN_ENUM_UINT8           enRegDomain,
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8    enServiceStatus
);


NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetCsServiceStatus(VOS_VOID);

NAS_MMC_SERVICE_ENUM_UINT8 NAS_MMC_GetPsServiceStatus(VOS_VOID);

VOS_VOID NAS_MMC_UpdateDomainServiceStatus(
    VOS_UINT8                           enCurrDomain,
    NAS_MMC_SERVICE_ENUM_UINT8          enCurrService
);


VOS_VOID    NAS_MMC_SetCsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enCsCurrService);


VOS_VOID    NAS_MMC_SetPsServiceStatus(NAS_MMC_SERVICE_ENUM_UINT8   enPsCurrService);

VOS_UINT32  NAS_MMC_GetNextAvailableTimerValue(VOS_VOID);

NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID);
VOS_VOID NAS_MMC_AddSysCfgIndex_SysCfg(VOS_VOID);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSettingRat_SysCfg(VOS_VOID);
VOS_VOID NAS_MMC_InitFsmCtx_SysCfg(VOS_VOID);
VOS_UINT32 NAS_MMC_GetPlmnSearchFlag_SysCfg(VOS_VOID);
VOS_VOID NAS_MMC_SetPlmnSearchFlag_SysCfg(VOS_UINT32 ulNeedSearchPlmnFlag);

VOS_VOID NAS_MMC_SetPrePrioRatList_SysCfg(
    NAS_MML_PLMN_RAT_PRIO_STRU          *pstPrePrioRatList
);

NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetPrePrioRatList_SysCfg(VOS_VOID);

NAS_MMC_SYSCFG_SETTING_CTRL_STRU* NAS_MMC_GetSysCfgSettingRecord_SysCfg(VOS_VOID);



/* L1 MAIN状态机上下文操作函数 */

VOS_UINT32  NAS_MMC_GetCurNormalAvailableTimerCount_L1Main(VOS_VOID);

VOS_VOID    NAS_MMC_ResetCurNormalAvailableTimerCount_L1Main(VOS_VOID);


VOS_VOID    NAS_MMC_AddCurNormalAvailableTimerCount_L1Main(VOS_VOID);

VOS_VOID   NAS_MMC_SetCurNormalAvailableTimerCount(
    VOS_UINT32                          ulCurTimerCount
);

VOS_VOID  NAS_MMC_AddAvailableTimerCount_OnPlmn(VOS_VOID);



VOS_UINT32  NAS_MMC_GetCurNcellSearchTimerCount_OnPlmn(VOS_VOID);
VOS_VOID  NAS_MMC_ResetCurNcellSearchTimerCount_OnPlmn(VOS_VOID);
VOS_VOID  NAS_MMC_AddCurNcellSearchTimerCount_OnPlmn(VOS_VOID);
VOS_UINT8  NAS_MMC_IsNeedStartNcellAvailableTimer(VOS_VOID);

VOS_VOID  NAS_MMC_SetAvailableTimerType_OnPlmn(
    NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8                 enAvailableTimerType
);
NAS_MMC_AVAILABLE_TIMER_TYPE_ENUM_UINT8  NAS_MMC_GetAvailableTimerType_OnPlmn(VOS_VOID);


NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_L1Main(VOS_VOID);
NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_L1Main(VOS_VOID);

VOS_VOID NAS_MMC_SetCsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
);

VOS_VOID NAS_MMC_SetPsRegAdditionalAction_L1Main(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
);

VOS_VOID NAS_MMC_ClearAllRegAdditionalAction_L1Main(VOS_VOID);

VOS_VOID NAS_MMC_SetCsRegAttemptCount_L1Main(
    VOS_UINT32      ulCsCount
);

VOS_VOID NAS_MMC_SetPsRegAttemptCount_L1Main(
    VOS_UINT32      ulPsCount
);

VOS_UINT32 NAS_MMC_GetCsRegAttemptCount_L1Main(VOS_VOID);

VOS_UINT32 NAS_MMC_GetPsRegAttemptCount_L1Main(VOS_VOID);

VOS_VOID NAS_MMC_ClearAllRegAttemptCount_L1Main(VOS_VOID);

/* 开机相关状态机上下文操作函数 */
NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn(VOS_VOID);
NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32   NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    enMmStartCnfFlg);
VOS_VOID    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn(VOS_VOID);
VOS_VOID    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32  enSimFileCnfFlg);
VOS_VOID    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MM_START_CNF_ENUM_UINT8    enMmStartCnfFlg);
VOS_VOID    NAS_MMC_SetWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_SIM_FILES_CNF_ENUM_UINT32 enSimFileCnfFlg);

/* 关机相关状态机上下文操作函数 */
NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetMmPowerOffCnfFlg_PowerOff(VOS_VOID);
NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8     NAS_MMC_GetAsPowerOffCnfFlg_PowerOff(VOS_VOID);

VOS_VOID    NAS_MMC_SetMmPowerOffCnfFlag_PowerOff(NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8   enMmPowerOffFlg);
VOS_VOID    NAS_MMC_SetAsPowerOffCnfFlag_PowerOff(NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8   enAsPowerOffFlg);

VOS_VOID    NAS_MMC_ClearMmPowerOffCnfFlag_PowerOff(NAS_MMC_MM_POWEROFF_FLAG_ENUM_UINT8   enMmPowerOffFlg);
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetMasterModeRat_PowerOff(VOS_VOID);

VOS_VOID NAS_MMC_SetMasterModeRat_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
);

NAS_MML_PLMN_RAT_PRIO_STRU* NAS_MMC_GetSlaveModeRatList_PowerOff(VOS_VOID);
VOS_VOID NAS_MMC_BuildSlaveModeRatList_PowerOff(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enMasterModeRat
);
VOS_VOID    NAS_MMC_ClearAsPowerOffCnfFlag_PowerOff(NAS_MMC_AS_POWEROFF_FLAG_ENUM_UINT8   enAsPowerOffFlg);
VOS_VOID    NAS_MMC_ClearAllMmPowerOffCnfFlag_PowerOff(VOS_VOID);
VOS_VOID    NAS_MMC_ClearAllAsPowerOffCnfFlag_PowerOff(VOS_VOID);

/* 异系统重选相关状态机上下文操作函数 */
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCellResel(VOS_VOID);
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCellResel(VOS_VOID);

MMC_RESUME_ORIGEN_ENUM_UINT8 NAS_MMC_GetResumeOrign_InterSysCellResel(VOS_VOID);
VOS_VOID NAS_MMC_SetResumeOrign_InterSysCellResel(
    MMC_RESUME_ORIGEN_ENUM_UINT8        enResumeOrign
);

VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);

VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);
VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCellResel(VOS_VOID);
VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCellResel(VOS_VOID);
VOS_VOID NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_UINT8   ucAbortFlg);
VOS_UINT8 NAS_MMC_GetAbortFlag_InterSysCellResel(VOS_VOID);
VOS_VOID NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_UINT8    ucSndSuspendRelReqFlg);
VOS_UINT8 NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel(VOS_VOID);



/* 异系统OOS相关状态机上下文操作函数 */
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysOos(VOS_VOID);
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysOos(VOS_VOID);

VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);

VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);
VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysOos(VOS_VOID);
VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysOos(VOS_VOID);

/* 异系统HO相关状态机上下文操作函数 */
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysHo(VOS_VOID);
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysHo(VOS_VOID);

VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);

VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);
VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysHo(VOS_VOID);
VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysHo(VOS_VOID);

VOS_VOID NAS_MMC_SetCsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
);
VOS_VOID NAS_MMC_SetPsSigExistFlag_InterSysHo(
    VOS_UINT8       ucSigExistFlg
);
VOS_UINT8  NAS_MMC_GetCsSigExistFlag_InterSysHo(VOS_VOID);
VOS_UINT8  NAS_MMC_GetPsSigExistFlag_InterSysHo(VOS_VOID);


/* 异系统CCO相关状态机上下文操作函数 */
NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8  NAS_MMC_GetSuspendRspFlg_InterSysCco(VOS_VOID);
NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8   NAS_MMC_GetResumeRspFlg_InterSysCco(VOS_VOID);

VOS_VOID NAS_MMC_ClearSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);

VOS_VOID NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_SUSPEND_RSP_FLAG_ENUM_UINT8 enMmSuspendRsp);
VOS_VOID NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_RESUME_RSP_FLAG_ENUM_UINT8 enMmResumeRsp);

VOS_VOID NAS_MMC_ClearAllSuspendRspFlag_InterSysCco(VOS_VOID);
VOS_VOID NAS_MMC_ClearAllResumeRspFlag_InterSysCco(VOS_VOID);

RRMM_RAT_PRIO_ENUM_UINT8 NAS_MMC_GetSpecRatPrio(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatList
);

VOS_UINT32 NAS_MMC_GetAbortFlag_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_SetAbortFlag_PlmnSelection(
    VOS_UINT8                          ucAbortFlg
);

VOS_UINT32 NAS_MMC_GetRelRequestFlag_PlmnSelection(VOS_VOID);

VOS_VOID NAS_MMC_SetRelRequestFlag_PlmnSelection(
    VOS_UINT8                           ucRelRequestFlg
);

VOS_VOID NAS_MMC_SetExistRplmnOrHplmnFlag_PlmnSelection(
    VOS_UINT8                           ucExistRplmnOrHplmnFlag
);

VOS_UINT8 NAS_MMC_GetExistRplmnOrHplmnFlag_PlmnSelection(VOS_VOID);



VOS_VOID NAS_MMC_SetInterSysSuspendRat_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetInterSysSuspendRat_PlmnSelection(VOS_VOID);

NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU * NAS_MMC_GetPlmnSelectionListInfo_PlmnSelection(VOS_VOID);

VOS_UINT8 NAS_MMC_GetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_SetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchedRoamPlmnSortedFlag
);
VOS_UINT8 NAS_MMC_GetSearchedRoamPlmnSortedFlag_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);



VOS_VOID NAS_MMC_SetAllBandSearch_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucAllBandSearch
);

VOS_VOID NAS_MMC_SetRatCoverage_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enCoverType
);

NAS_MMC_RAT_SEARCH_INFO_STRU* NAS_MMC_GetRatCoverage_PlmnSelection(VOS_VOID);

VOS_UINT8 NAS_MMC_GetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

VOS_VOID NAS_MMC_SetSearchRplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndHplmnFlg
);


VOS_VOID NAS_MMC_SetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSearchRplmnAndEplmnFlg
);
VOS_UINT8 NAS_MMC_GetSearchRplmnAndEplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);


/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, begin */
VOS_UINT8 NAS_MMC_GetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
VOS_VOID NAS_MMC_SetSearchDplmnAndHplmnFlg_PlmnSelection(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           ucSwithOnAddHplmnFlg
);
/* Modified by c00318887 for DPlmn扩容和优先接入HPLMN, 2015-5-18, end */

VOS_VOID NAS_MMC_InitSearchRatInfo_PlmnSelection(VOS_VOID);

NAS_MML_FORBIDPLMN_ROAMING_LAS_INFO_STRU* NAS_MMC_GetForbRoamLaInfo_PlmnSelection(VOS_VOID);


NAS_MML_PLMN_ID_STRU* NAS_MMC_GetForbPlmnForGrpsInfo_PlmnSelection(VOS_VOID);

NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurrSearchingPlmn_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_SetCurrSearchingPlmn_PlmnSelection(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstPlmnId
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_SetCsPsMode1ReCampLtePlmn_PlmnSelection(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
);

NAS_MML_PLMN_ID_STRU* NAS_MMC_GetCsPsMode1ReCampLtePlmn_PlmnSelection(VOS_VOID);
#endif

VOS_UINT32 NAS_MMC_GetAbortFlag_AnyCellSearch(VOS_VOID);
VOS_VOID NAS_MMC_SetAbortFlag_AnyCellSearch(
    VOS_UINT8                           ucAbortFlg
);
NAS_MMC_FSM_ANYCELL_SEARCH_CTX_STRU* NAS_MMC_GetFsmCtxAddr_AnyCellSearch(VOS_VOID);

VOS_UINT8 NAS_MMC_GetRatNum_AnyCellSearch(VOS_VOID);

NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetNextSearchRat_AnyCellSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetSearchedFlag_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
);

VOS_VOID NAS_MMC_SetRatPrioList_AnyCellSearch(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
);




NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetCsRegCause_PlmnSelection(VOS_VOID);
NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16 NAS_MMC_GetPsRegCause_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_SetCsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCsCause
);
VOS_VOID NAS_MMC_SetPsRegCause_PlmnSelection(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enPsCause
);

VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_PlmnSelection(VOS_VOID);
VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_SetWaitRegRsltFlag_PlmnSelection(VOS_UINT8 usWaitFlag);
VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnSelection(
    VOS_UINT8                           ucRegDomain
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnSelection(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnSelection(VOS_VOID);
VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
);
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnSelection(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
);



VOS_VOID NAS_MMC_SetSysCfgSendingOrder_SysCfg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
);

VOS_UINT32 NAS_MMC_IsCurrentPlmnIdRoamingAllowed_SysCfg(
    MMA_MMC_SYS_CFG_SET_REQ_STRU        *pstSysCfgSetParm
);


VOS_UINT8 NAS_MMC_GetRelRequestFlag_SysCfg(VOS_VOID);
VOS_VOID NAS_MMC_SetRelRequestFlag_SysCfg(
    VOS_UINT8                           ucRelRequestFlg
);

/******************LIST 搜网状态机上下文操作函数 **********************/
VOS_VOID    NAS_MMC_InitSearchRatInfo_PlmnList(VOS_VOID);

NAS_MMC_PLMN_LIST_SEARCH_CTRL_STRU *NAS_MMC_GetSearchCtrlInfo_PlmnList(VOS_VOID);

VOS_UINT32  NAS_MMC_GetNextSearchingRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
);

VOS_VOID    NAS_MMC_GetOrigenSearchRat_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penRat
);

VOS_VOID    NAS_MMC_SetSearchedFlag_PlmnList(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSpecRat
);

VOS_UINT8   NAS_MMC_GetAbortFlag_PlmnList(VOS_VOID);
VOS_VOID    NAS_MMC_SetAbortFlag_PlmnList(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8   NAS_MMC_GetNotifyMmaFlag_PlmnList(VOS_VOID);
VOS_VOID    NAS_MMC_SetNotifyMmaFlag_PlmnList(
    VOS_UINT8                           ucNotifyFlg
);

VOS_UINT8   NAS_MMC_GetWaitRegRsltFlag_PlmnList(VOS_VOID);
VOS_VOID    NAS_MMC_SetWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucWaitFlag
);

VOS_VOID    NAS_MMC_ClearSingleDomainWaitRegRsltFlag_PlmnList(
    VOS_UINT8       ucRegDomain
);
VOS_VOID    NAS_MMC_ClearAllWaitRegRsltFlag_PlmnList(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_PlmnList(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_PlmnList(VOS_VOID);

VOS_VOID NAS_MMC_SetCsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
);
VOS_VOID NAS_MMC_SetPsRegAdditionalAction_PlmnList(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8  enPsAddtionalAction
);

NAS_MMC_PLMN_LIST_REG_RSLT_INFO_STRU *NAS_MMC_GetRegRsltInfo_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_InitSearchedPlmnListInfo_PlmnList(VOS_VOID);

NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU *NAS_MMC_GetSearchedPlmnListInfo_PlmnList(VOS_VOID);

VOS_VOID    NAS_MMC_UpdateSearchedPlmnListInfo_PlmnList(
    RRC_PLMN_ID_LIST_STRU              *pstRrcList
);


#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT8 NAS_MMC_GetPreLteDisableFlg_PlmnList(VOS_VOID);
VOS_VOID NAS_MMC_SetPreLteDisableFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
);
#endif


VOS_UINT8   NAS_MMC_GetAnyCellSrchFlg_PlmnList(VOS_VOID);
VOS_VOID    NAS_MMC_SetAnyCellSrchFlg_PlmnList(
    VOS_UINT8                           ucPreLteDisableFlg
);


VOS_VOID NAS_MMC_InitHighPrioPlmnSearchCtx(NAS_MMC_HIGH_PRIO_PLMN_SEARCH_CTRL_CTX_STRU *pstHighPrioPlmnSearchCtrl);


MMA_MMC_NET_SCAN_REQ_STRU *NAS_MMC_GetNetScanReq(VOS_VOID);

VOS_VOID NAS_MMC_SetNetScanReq(
    MMA_MMC_NET_SCAN_REQ_STRU          *pstNetScanReq
);

NAS_MMC_PLMN_SELECTION_LIST_INFO_STRU *NAS_MMC_GetHighPrioPlmnList(VOS_VOID);
VOS_UINT16 NAS_MMC_GetHighPrioPlmnNum(VOS_VOID);

NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSelectionListType(VOS_VOID);
VOS_VOID NAS_MMC_SetPlmnSelectionListType(
    NAS_MMC_PLMN_SELECTION_LIST_TYPE_ENUM_UINT8             enPlmnSelectionListType       
);

VOS_UINT8 NAS_MMC_GetTdHighRatSearchCount(VOS_VOID);
VOS_VOID NAS_MMC_AddTdHighRatSearchCount(VOS_VOID);
VOS_VOID NAS_MMC_InitTdHighRatSearchCount(VOS_VOID);

VOS_UINT32 NAS_MMC_GetEHPlmn(
    RRC_PLMN_ID_STRU                   *pstEHPlmn,
    VOS_UINT8                          *pucEHPlmnNum
);


VOS_VOID NAS_MMC_SetPlmnSelectionMode(
    NAS_MMC_PLMN_SELECTION_MODE_ENUM_UINT8  enSelectionMode
);

VOS_VOID NAS_MMC_SaveUserReselPlmnInfo(VOS_VOID);

NAS_MMC_CONTEXT_STRU* NAS_MMC_GetMmcCtxAddr(VOS_VOID);
NAS_MMC_FSM_CTX_STRU* NAS_MMC_GetCurFsmAddr(VOS_VOID);
NAS_MMC_FSM_STACK_STRU* NAS_MMC_GetFsmStackAddr(VOS_VOID);
NAS_FSM_DESC_STRU* NAS_MMC_GetCurFsmDesc(VOS_VOID);
NAS_MMC_ENTRY_MSG_STRU* NAS_MMC_GetCurrFsmMsgAddr(VOS_VOID);
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetCurrFsmId(VOS_VOID);
VOS_UINT32 NAS_MMC_GetCurrFsmEventType(VOS_VOID);
NAS_MMC_FSM_ID_ENUM_UINT32 NAS_MMC_GetParentFsmId(VOS_VOID);
VOS_UINT32 NAS_MMC_GetParentFsmEventType(VOS_VOID);

NAS_MMC_FSM_EXTRA_CTX_UNION* NAS_MMC_GetParentFsmCtx(VOS_VOID);
    
NAS_MMC_MSG_QUEUE_STRU* NAS_MMC_GetCachMsgBufferAddr(VOS_VOID);

VOS_VOID NAS_MMC_UpdatePlmnRegInfoList(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
);


VOS_VOID NAS_MMC_GetHplmnRejDomainInfo(
    VOS_UINT8                          *pucRejDomainRlst
);

VOS_VOID NAS_MMC_ClearHplmnRejDomainInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmn,
    VOS_UINT8                           ucAcceptCnDomain
);

VOS_VOID  NAS_MMC_SetPlmnRegRejInfo(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MMC_REG_DOMAIN_ENUM_UINT8       enDomain,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,
    NAS_MMC_PLMN_REG_INFO_STRU         *pstPlmnRegInfo
);

VOS_UINT32 NAS_MMC_GetAbortEventType_BgPlmnSearch(VOS_VOID);
VOS_VOID NAS_MMC_SetAbortEventType_BgPlmnSearch(
    VOS_UINT32                          ulAbortEventType
);


NAS_MMC_ABORT_FSM_TYPE_UINT8 NAS_MMC_GetAbortType_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetAbortType_BgPlmnSearch(
    NAS_MMC_ABORT_FSM_TYPE_UINT8        enAbortType
);

VOS_UINT8 NAS_MMC_GetRelRequestFlag_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetRelRequestFlag_BgPlmnSearch(
    VOS_UINT8                           ucRelRequestFlg
);

VOS_UINT8 NAS_MMC_GetWaitRegRsltFlag_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucWaitFlag
);

VOS_VOID NAS_MMC_ClearSingleDomainWaitRegRsltFlag_BgPlmnSearch(
    VOS_UINT8                           ucRegDomain
);

VOS_VOID NAS_MMC_ClearAllWaitRegRsltFlag_BgPlmnSearch(VOS_VOID);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetCsRegAdditionalAction_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetCsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enCsAddtionalAction
);

NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 NAS_MMC_GetPsRegAdditionalAction_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetPsRegAdditionalAction_BgPlmnSearch(
    NAS_MMC_ADDITIONAL_ACTION_ENUM_UINT8 enPsAddtionalAction
);

NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetCurHighPrioPlmn_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetCurHighPrioPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);

NAS_MML_PLMN_WITH_RAT_STRU* NAS_MMC_GetPreCampPlmn_BgPlmnSearch(VOS_VOID);

VOS_VOID NAS_MMC_SetPreCampPlmn_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
VOS_VOID NAS_MMC_SetPreCampPlmnRat_BgPlmnSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
);
VOS_VOID NAS_MMC_SetPreEquPlmnInfo_BgPlmnSearch(
    NAS_MML_PLMN_ID_STRU               *pstCurrCampPlmnId,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID);
VOS_VOID NAS_MMC_SetPreLteDisableFlg_BgPlmnSearch(
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapStatus
);

VOS_UINT32 NAS_MMC_GetPreLteDisableFlg_BgPlmnSearch(VOS_VOID);


VOS_VOID NAS_MMC_SetNeedEnableLteFlg_BgPlmnSearch(
    VOS_UINT8                                               ucNeedEnableLteFlg);
VOS_UINT32 NAS_MMC_GetNeedEnableLteFlg_BgPlmnSearch(VOS_VOID);

NAS_MML_EQUPLMN_INFO_STRU* NAS_MMC_GetPreEquPlmnInfo_BgPlmnSearch(VOS_VOID);
VOS_VOID NAS_MMC_SetFirstStartHPlmnTimerFlg(
    VOS_UINT8                           ucFirstStartHPlmnTimer
);

VOS_UINT8 NAS_MMC_GetFirstStartHPlmnTimerFlg(VOS_VOID);

VOS_UINT32  NAS_MMC_GetHplmnTimerLen( VOS_VOID );

VOS_UINT32  NAS_MMC_GetCacheNum( VOS_VOID );

VOS_UINT16  NAS_MMC_GetFsmStackPopFlg( VOS_VOID ) ;

VOS_VOID  NAS_MMC_SetFsmStackPopFlg(
    VOS_UINT16                          ucStachPopFlg
);

VOS_UINT32 NAS_MMC_IsFsmEntryEventType(
    VOS_UINT32                          ulEventType
);

VOS_VOID NAS_MMC_SetBufferedPlmnSearchInfo(
    VOS_UINT32                                              ulPlmnSearchFlg,
    NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32                   enPlmnSearchScene
);


VOS_UINT32  NAS_MMC_GetBufferedPlmnSearchFlg( VOS_VOID );

NAS_MMC_PLMN_SEARCH_SCENE_ENUM_UINT32  NAS_MMC_GetBufferedPlmnSearchScene( VOS_VOID );

VOS_VOID NAS_MMC_UpdateGURegRlstRPlmnIdInNV(VOS_VOID);

NAS_MMC_SRV_STA_CHNG_INFO_STRU* NAS_MMC_GetSrvStaChngInfo( VOS_VOID );

VOS_UINT32  NAS_MMC_IsFsmIdInFsmStack(
    NAS_MMC_FSM_ID_ENUM_UINT32          enFsmId
);

VOS_UINT8 NAS_MMC_GetNeedSndSysInfo_BgPlmnSearch(VOS_VOID);
VOS_VOID NAS_MMC_SetNeedSndSysInfo_BgPlmnSearch(
    VOS_UINT8                           ucNeedSndSysInfo
);

VOS_UINT32 NAS_MMC_NeedTrigPlmnSrch_UserSpecCurrentPlmn(VOS_VOID);


VOS_VOID NAS_MMC_DelMsUnsupportRat(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList
);

VOS_VOID NAS_MMC_SetUtranSkipWPlmnSearchFlag(VOS_UINT8 ucUtranSkipWPlmnSearchFlag);
VOS_UINT8 NAS_MMC_GetUtranSkipWPlmnSearchFlag(VOS_VOID);
VOS_VOID NAS_MMC_SetOtherModemPlmnId(NAS_MML_PLMN_ID_STRU *pstPlmnId);
NAS_MML_PLMN_ID_STRU* NAS_MMC_GetOtherModemPlmnId(VOS_VOID);


VOS_UINT8 NAS_MMC_GetNcellSearchFlag(VOS_VOID);
VOS_VOID NAS_MMC_SetNcellSearchFlag(VOS_UINT8 ucNcellSearchFlag);


VOS_UINT8 NAS_MMC_GetNcellSearchFirstTimerLen(VOS_VOID);
VOS_VOID NAS_MMC_SetNcellSearchFirstTimerLen(VOS_UINT8 ucNcellSearchTimerLen);

VOS_VOID NAS_MMC_SetNcellSearchSecondTimerLen(VOS_UINT8 ucNcellSearchTimerLen);
VOS_UINT8 NAS_MMC_GetNcellSearchSecondTimerLen(VOS_VOID);


NAS_MMC_NCELL_SEARCH_INFO_STRU* NAS_MMC_GetNcellSearchInfo(VOS_VOID);
VOS_VOID NAS_MMC_SetNcellSearchInfo(NAS_MMC_NCELL_SEARCH_INFO_STRU *pstNcellSearchInfo);


VOS_UINT32 NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen(VOS_VOID);

VOS_UINT8  NAS_MMC_GetPlmnSrchNoRfFlg( VOS_VOID );
NAS_MML_NET_RAT_TYPE_ENUM_UINT8 NAS_MMC_GetPlmnSrchNoRfRatType( VOS_VOID );
VOS_VOID  NAS_MMC_SetPlmnSrchNoRfFlg( 
    VOS_UINT8                           ucPlmnSrchNoRfFlg
);
VOS_VOID  NAS_MMC_SetCurrRatPlmnSrchNoRfFlg(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    VOS_UINT8                           ucPlmnSrchNoRfFlg
);

VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerLen( VOS_VOID );

VOS_UINT32  NAS_MMC_GetHighPrioRatHplmnTimerRetryLen( VOS_VOID );

VOS_UINT8  NAS_MMC_GetHighPrioRatHplmnTimerActiveFlg( VOS_VOID );

VOS_UINT32  NAS_MMC_GetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID);

VOS_VOID    NAS_MMC_ResetCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID);

VOS_VOID    NAS_MMC_AddCurHighPrioRatHplmnTimerFirstSearchCount_L1Main(VOS_VOID);


VOS_VOID NAS_MMC_SetEnableLteTimerExpireFlag(
    VOS_UINT8                           ucEnableLteTimerExpireFlag
);
VOS_UINT8 NAS_MMC_GetEnableLteTimerExpireFlag( VOS_VOID );
NAS_MML_PLMN_ID_STRU *NAS_MMC_GetDisabledLtePlmnId(VOS_VOID);
VOS_VOID NAS_MMC_SetDisabledLtePlmnId(
    NAS_MML_PLMN_ID_STRU              *pstPlmnId
);
VOS_VOID NAS_MMC_ClearDisabledLtePlmnId(VOS_VOID);

VOS_VOID  NAS_MMC_InitUserDPlmnNPlmnInfo(
    NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU                 *pstDPlmnNPlmnCfgInfo
);
NAS_MMC_DPLMN_NPLMN_CFG_INFO_STRU* NAS_MMC_GetDPlmnNPlmnCfgInfo( VOS_VOID );


NAS_MMC_REG_CONTROL_ENUM_UINT8 NAS_MMC_GetRegCtrl( VOS_VOID );

VOS_VOID NAS_MMC_SetRegCtrl(
    NAS_MMC_REG_CONTROL_ENUM_UINT8      enRegCtrl
);

VOS_UINT8 NAS_MMC_GetAsAnyCampOn( VOS_VOID );

VOS_VOID NAS_MMC_SetAsAnyCampOn(
    VOS_UINT8                          ucAsAnyCampOn
);

VOS_VOID NAS_MMC_SaveRegReqNCellInfo(
    MMA_MMC_REG_CELL_INFO_STRU         *pstCellInfo
);
#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID NAS_MMC_SetRatChgForLteOos2GPrefPlmnSelFlg(VOS_UINT8 ucRatChgForLteOos2GPrefPlmnSelFlg);
extern VOS_UINT8 NAS_MMC_GetRatChgForLteOos2GPrefPlmnSelFlg(VOS_VOID);
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasMmcCtx.h */
