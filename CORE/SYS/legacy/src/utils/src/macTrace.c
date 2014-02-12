/*
 * Copyright (c) 2012-2013 Qualcomm Atheros, Inc.
 * All Rights Reserved.
 * Qualcomm Atheros Confidential and Proprietary.
 */
/**=========================================================================
* Copyright (c) 2013 Qualcomm Atheros, Inc.
* All Rights Reserved.
* Qualcomm Atheros Confidential and Proprietary.
  \file  macTrace.c

  \brief implementation for trace related APIs

  \author Sunit Bhatia

   Copyright 2008 (c) Qualcomm, Incorporated.  All Rights Reserved.

   Qualcomm Confidential and Proprietary.

  ========================================================================*/


/*--------------------------------------------------------------------------
  Include Files
  ------------------------------------------------------------------------*/

#include "macTrace.h"
#include "wlan_qct_wda.h"

#include "wlan_hdd_assoc.h"
#include "wlan_hdd_main.h"
#ifdef CONFIG_CFG80211
#include "wlan_hdd_p2p.h"
#endif
#include "csrNeighborRoam.h"
#include "csrInternal.h"
#include "limGlobal.h"
#include "wlan_qct_tl.h"
#include "vos_trace.h"

#ifdef TRACE_RECORD

/* ---------------------------------------------------------------------------
    \fn macTraceGetHDDWlanConnState
    \function to get string equivalent of a value
	 from the enum eConnectionState.

    \param connState - the value from the enum
    \return the string equivalent of connState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetHDDWlanConnState(tANI_U16 connState)
{
    switch(connState)
    {
        CASE_RETURN_STRING(eConnectionState_NotConnected);
        CASE_RETURN_STRING(eConnectionState_Connecting);
        CASE_RETURN_STRING(eConnectionState_Associated);
        CASE_RETURN_STRING(eConnectionState_IbssDisconnected);
        CASE_RETURN_STRING(eConnectionState_IbssConnected);
        CASE_RETURN_STRING(eConnectionState_Disconnecting);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetP2PConnState
    \function to get string equivalent of a value
	 from the enum tP2PConnectionStatus.

    \param connState - the value from the enum
    \return the string equivalent of connState
  ---------------------------------------------------------------------------*/
#ifdef WLAN_FEATURE_P2P_DEBUG
tANI_U8* macTraceGetP2PConnState(tANI_U16 connState)
{
    switch(connState)
    {
        CASE_RETURN_STRING(P2P_NOT_ACTIVE);
        CASE_RETURN_STRING(P2P_GO_NEG_PROCESS);
        CASE_RETURN_STRING(P2P_GO_NEG_COMPLETED);
        CASE_RETURN_STRING(P2P_CLIENT_CONNECTING_STATE_1);
        CASE_RETURN_STRING(P2P_GO_COMPLETED_STATE);
        CASE_RETURN_STRING(P2P_CLIENT_CONNECTED_STATE_1);
        CASE_RETURN_STRING(P2P_CLIENT_DISCONNECTED_STATE);
        CASE_RETURN_STRING(P2P_CLIENT_CONNECTING_STATE_2);
        CASE_RETURN_STRING(P2P_CLIENT_COMPLETED_STATE);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}
#endif

/* ---------------------------------------------------------------------------
    \fn macTraceGetNeighbourRoamState
    \function to get string equivalent of a value
	 from the enum eCsrNeighborRoamState.

    \param neighbourRoamState - the value from the enum
    \return the string equivalent of neighbourRoamState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetNeighbourRoamState(tANI_U16 neighbourRoamState)
{
    switch(neighbourRoamState)
    {
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_CLOSED);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_INIT);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_CONNECTED);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_CFG_CHAN_LIST_SCAN);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_REASSOCIATING);
        #ifdef WLAN_FEATURE_VOWIFI_11R
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_REPORT_QUERY);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_REPORT_SCAN);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_PREAUTHENTICATING);
        CASE_RETURN_STRING(eCSR_NEIGHBOR_ROAM_STATE_PREAUTH_DONE);
        #endif /* WLAN_FEATURE_VOWIFI_11R */
        CASE_RETURN_STRING(eNEIGHBOR_STATE_MAX);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetcsrRoamState
    \function to get string equivalent of a value
	 from the enum eCsrRoamState.

    \param csrRoamState - the value from the enum
    \return the string equivalent of csrRoamState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetcsrRoamState(tANI_U16 csrRoamState)
{
    switch(csrRoamState)
    {
        CASE_RETURN_STRING(eCSR_ROAMING_STATE_STOP);
        CASE_RETURN_STRING(eCSR_ROAMING_STATE_IDLE);
        CASE_RETURN_STRING(eCSR_ROAMING_STATE_SCANNING);
        CASE_RETURN_STRING(eCSR_ROAMING_STATE_JOINING);
        CASE_RETURN_STRING(eCSR_ROAMING_STATE_JOINED);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetcsrRoamSubState
    \function to get string equivalent of a value
	 from the enum eCsrRoamSubState.

    \param csrRoamSubState - the value from the enum
    \return the string equivalent of csrRoamSubState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetcsrRoamSubState(tANI_U16 csrRoamSubState)
{
    switch(csrRoamSubState)
    {
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_NONE);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_START_BSS_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_JOIN_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_REASSOC_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISASSOC_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_STOP_BSS_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISCONNECT_CONTINUE_ROAMING);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_AUTH_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_CONFIG);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DEAUTH_REQ);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISASSOC_NOTHING_TO_JOIN);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISASSOC_REASSOC_FAILURE);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISASSOC_FORCED);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_WAIT_FOR_KEY);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_DISASSOC_HANDOFF);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_JOINED_NO_TRAFFIC);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_JOINED_NON_REALTIME_TRAFFIC);
        CASE_RETURN_STRING(eCSR_ROAM_SUBSTATE_JOINED_REALTIME_TRAFFIC);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetLimSmeState
    \function to get string equivalent of a value
	 from the enum tLimSmeStates.

    \param limState - the value from the enum
    \return the string equivalent of limState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetLimSmeState(tANI_U16 limState)
{
    switch(limState)
    {
        CASE_RETURN_STRING(eLIM_SME_OFFLINE_STATE);
        CASE_RETURN_STRING(eLIM_SME_IDLE_STATE);
        CASE_RETURN_STRING(eLIM_SME_SUSPEND_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_SCAN_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_JOIN_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_AUTH_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_ASSOC_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_REASSOC_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_REASSOC_LINK_FAIL_STATE);
        CASE_RETURN_STRING(eLIM_SME_JOIN_FAILURE_STATE);
        CASE_RETURN_STRING(eLIM_SME_ASSOCIATED_STATE);
        CASE_RETURN_STRING(eLIM_SME_REASSOCIATED_STATE);
        CASE_RETURN_STRING(eLIM_SME_LINK_EST_STATE);
        CASE_RETURN_STRING(eLIM_SME_LINK_EST_WT_SCAN_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_PRE_AUTH_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_DISASSOC_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_DEAUTH_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_START_BSS_STATE);
        CASE_RETURN_STRING(eLIM_SME_WT_STOP_BSS_STATE);
        CASE_RETURN_STRING(eLIM_SME_NORMAL_STATE);
        CASE_RETURN_STRING(eLIM_SME_CHANNEL_SCAN_STATE);
        CASE_RETURN_STRING(eLIM_SME_NORMAL_CHANNEL_SCAN_STATE);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetLimMlmState
    \function to get string equivalent of a value
	 from the enum tLimMlmStates.

    \param mlmState - the value from the enum
    \return the string equivalent of mlmState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetLimMlmState(tANI_U16 mlmState)
{
    switch(mlmState)
    {
        CASE_RETURN_STRING(eLIM_MLM_OFFLINE_STATE);
        CASE_RETURN_STRING(eLIM_MLM_IDLE_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_PROBE_RESP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_PASSIVE_SCAN_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_JOIN_BEACON_STATE);
        CASE_RETURN_STRING(eLIM_MLM_JOINED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_BSS_STARTED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_AUTH_FRAME2_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_AUTH_FRAME3_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_AUTH_FRAME4_STATE);
        CASE_RETURN_STRING(eLIM_MLM_AUTH_RSP_TIMEOUT_STATE);
        CASE_RETURN_STRING(eLIM_MLM_AUTHENTICATED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ASSOC_RSP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_REASSOC_RSP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_ASSOCIATED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_REASSOCIATED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_LINK_ESTABLISHED_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ASSOC_CNF_STATE);
        CASE_RETURN_STRING(eLIM_MLM_LEARN_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ADD_BSS_RSP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_DEL_BSS_RSP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ADD_BSS_RSP_ASSOC_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ADD_BSS_RSP_REASSOC_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ADD_BSS_RSP_PREASSOC_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_ADD_STA_RSP_STATE);
        CASE_RETURN_STRING(eLIM_MLM_WT_DEL_STA_RSP_STATE);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

/* ---------------------------------------------------------------------------
    \fn macTraceGetTLState
    \function to get string equivalent of a value
	 from the enum WLANTL_STAStateType.

    \param tlState - the value from the enum
    \return the string equivalent of tlState
  ---------------------------------------------------------------------------*/
tANI_U8* macTraceGetTLState(tANI_U16 tlState)
{
   switch(tlState)
    {
        CASE_RETURN_STRING(WLANTL_STA_INIT);
        CASE_RETURN_STRING(WLANTL_STA_CONNECTED);
        CASE_RETURN_STRING(WLANTL_STA_AUTHENTICATED);
        CASE_RETURN_STRING(WLANTL_STA_DISCONNECTED);
        CASE_RETURN_STRING(WLANTL_STA_MAX_STATE);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
   }
}

tANI_U8* macTraceGetSmeMsgString( tANI_U16 smeMsg )
{
    switch( smeMsg )
    {
        CASE_RETURN_STRING(eWNI_SME_START_REQ);
        CASE_RETURN_STRING(eWNI_SME_START_RSP);
        CASE_RETURN_STRING(eWNI_SME_SYS_READY_IND);
        CASE_RETURN_STRING(eWNI_SME_SCAN_REQ);
        CASE_RETURN_STRING(eWNI_SME_SCAN_ABORT_IND);
        CASE_RETURN_STRING(eWNI_SME_SCAN_RSP);
#ifdef FEATURE_OEM_DATA_SUPPORT
        CASE_RETURN_STRING(eWNI_SME_OEM_DATA_REQ);
        CASE_RETURN_STRING(eWNI_SME_OEM_DATA_RSP);
#endif
        CASE_RETURN_STRING(eWNI_SME_JOIN_REQ);
        CASE_RETURN_STRING(eWNI_SME_JOIN_RSP);
        CASE_RETURN_STRING(eWNI_SME_SETCONTEXT_REQ);
        CASE_RETURN_STRING(eWNI_SME_SETCONTEXT_RSP);
        CASE_RETURN_STRING(eWNI_SME_REASSOC_REQ);
        CASE_RETURN_STRING(eWNI_SME_REASSOC_RSP);
        CASE_RETURN_STRING(eWNI_SME_AUTH_REQ);
        CASE_RETURN_STRING(eWNI_SME_AUTH_RSP);
        CASE_RETURN_STRING(eWNI_SME_DISASSOC_REQ);
        CASE_RETURN_STRING(eWNI_SME_DISASSOC_RSP);
        CASE_RETURN_STRING(eWNI_SME_DISASSOC_IND);
        CASE_RETURN_STRING(eWNI_SME_DISASSOC_CNF);
        CASE_RETURN_STRING(eWNI_SME_DEAUTH_REQ);
        CASE_RETURN_STRING(eWNI_SME_DEAUTH_RSP);
        CASE_RETURN_STRING(eWNI_SME_DEAUTH_IND);
        CASE_RETURN_STRING(eWNI_SME_WM_STATUS_CHANGE_NTF);
        CASE_RETURN_STRING(eWNI_SME_IBSS_NEW_PEER_IND);
        CASE_RETURN_STRING(eWNI_SME_IBSS_PEER_DEPARTED_IND);
        CASE_RETURN_STRING(eWNI_SME_START_BSS_REQ);
        CASE_RETURN_STRING(eWNI_SME_START_BSS_RSP);
        CASE_RETURN_STRING(eWNI_SME_AUTH_IND);
        CASE_RETURN_STRING(eWNI_SME_ASSOC_IND);
        CASE_RETURN_STRING(eWNI_SME_ASSOC_CNF);
        CASE_RETURN_STRING(eWNI_SME_REASSOC_IND);
        CASE_RETURN_STRING(eWNI_SME_REASSOC_CNF);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_REQ);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_RSP);
        CASE_RETURN_STRING(eWNI_SME_STOP_BSS_REQ);
        CASE_RETURN_STRING(eWNI_SME_STOP_BSS_RSP);
        CASE_RETURN_STRING(eWNI_SME_DEL_BA_PEER_IND);
        CASE_RETURN_STRING(eWNI_SME_DEFINE_QOS_REQ);
        CASE_RETURN_STRING(eWNI_SME_DEFINE_QOS_RSP);
        CASE_RETURN_STRING(eWNI_SME_DELETE_QOS_REQ);
        CASE_RETURN_STRING(eWNI_SME_DELETE_QOS_RSP);
        CASE_RETURN_STRING(eWNI_SME_PROMISCUOUS_MODE_REQ);
        CASE_RETURN_STRING(eWNI_SME_PROMISCUOUS_MODE_RSP);
        CASE_RETURN_STRING(eWNI_SME_LINK_TEST_START_REQ);
        CASE_RETURN_STRING(eWNI_SME_LINK_TEST_START_RSP);
        CASE_RETURN_STRING(eWNI_SME_LINK_TEST_STOP_REQ);
        CASE_RETURN_STRING(eWNI_SME_LINK_TEST_STOP_RSP);
        CASE_RETURN_STRING(eWNI_SME_LINK_TEST_REPORT_IND);
        CASE_RETURN_STRING(eWNI_SME_NEIGHBOR_BSS_IND);
        CASE_RETURN_STRING(eWNI_SME_MEASUREMENT_REQ);
        CASE_RETURN_STRING(eWNI_SME_MEASUREMENT_RSP);
        CASE_RETURN_STRING(eWNI_SME_MEASUREMENT_IND);
        CASE_RETURN_STRING(eWNI_SME_SET_WDS_INFO_REQ);
        CASE_RETURN_STRING(eWNI_SME_SET_WDS_INFO_RSP);
        CASE_RETURN_STRING(eWNI_SME_WDS_INFO_IND);
        CASE_RETURN_STRING(eWNI_SME_SET_POWER_REQ);
        CASE_RETURN_STRING(eWNI_SME_SET_POWER_RSP);
        CASE_RETURN_STRING(eWNI_SME_CLIENT_SIDE_LOAD_BALANCE_REQ);
        CASE_RETURN_STRING(eWNI_SME_CLIENT_SIDE_LOAD_BALANCE_RSP);
        CASE_RETURN_STRING(eWNI_SME_SELECT_CHANNEL_REQ);
        CASE_RETURN_STRING(eWNI_SME_SELECT_CHANNEL_RSP);
        CASE_RETURN_STRING(eWNI_SME_SET_PROPRIETARY_IE_REQ);
        CASE_RETURN_STRING(eWNI_SME_SET_PROPRIETARY_IE_RSP); // #endif
        CASE_RETURN_STRING(eWNI_SME_DISCARD_SKB_NTF);  // Used to cleanup SKBs by HDD
        CASE_RETURN_STRING(eWNI_SME_DEAUTH_CNF);
        CASE_RETURN_STRING(eWNI_SME_MIC_FAILURE_IND);
        CASE_RETURN_STRING(eWNI_SME_ADDTS_REQ);
        CASE_RETURN_STRING(eWNI_SME_ADDTS_RSP);
        CASE_RETURN_STRING(eWNI_SME_ADDTS_CNF);
        CASE_RETURN_STRING(eWNI_SME_ADDTS_IND);
        CASE_RETURN_STRING(eWNI_SME_DELTS_REQ);
        CASE_RETURN_STRING(eWNI_SME_DELTS_RSP);
        CASE_RETURN_STRING(eWNI_SME_DELTS_IND);
        CASE_RETURN_STRING(eWNI_SME_SET_BACKGROUND_SCAN_MODE_REQ);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_CB_PRIMARY_REQ);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_CB_PRIMARY_RSP);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_CB_SECONDARY_REQ);
        CASE_RETURN_STRING(eWNI_SME_SWITCH_CHL_CB_SECONDARY_RSP);
        CASE_RETURN_STRING(eWNI_SME_PROBE_REQ);
        CASE_RETURN_STRING(eWNI_SME_STA_STAT_REQ);
        CASE_RETURN_STRING(eWNI_SME_STA_STAT_RSP);
        CASE_RETURN_STRING(eWNI_SME_AGGR_STAT_REQ);
        CASE_RETURN_STRING(eWNI_SME_AGGR_STAT_RSP);
        CASE_RETURN_STRING(eWNI_SME_GLOBAL_STAT_REQ);
        CASE_RETURN_STRING(eWNI_SME_GLOBAL_STAT_RSP);
        CASE_RETURN_STRING(eWNI_SME_STAT_SUMM_REQ);
        CASE_RETURN_STRING(eWNI_SME_STAT_SUMM_RSP);
        CASE_RETURN_STRING(eWNI_SME_REMOVEKEY_REQ);
        CASE_RETURN_STRING(eWNI_SME_REMOVEKEY_RSP);
        CASE_RETURN_STRING(eWNI_SME_GET_SCANNED_CHANNEL_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_SCANNED_CHANNEL_RSP);
        CASE_RETURN_STRING(eWNI_SME_SET_TX_POWER_REQ);
        CASE_RETURN_STRING(eWNI_SME_SET_TX_POWER_RSP);
        CASE_RETURN_STRING(eWNI_SME_GET_TX_POWER_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_TX_POWER_RSP);
        CASE_RETURN_STRING(eWNI_SME_GET_NOISE_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_NOISE_RSP);
        CASE_RETURN_STRING(eWNI_SME_LOW_RSSI_IND);
        CASE_RETURN_STRING(eWNI_SME_GET_STATISTICS_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_STATISTICS_RSP);
        CASE_RETURN_STRING(eWNI_SME_GET_RSSI_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_ASSOC_STAS_REQ);
        CASE_RETURN_STRING(eWNI_SME_TKIP_CNTR_MEAS_REQ);
        CASE_RETURN_STRING(eWNI_SME_UPDATE_APWPSIE_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_WPSPBC_SESSION_REQ);
        CASE_RETURN_STRING(eWNI_SME_WPS_PBC_PROBE_REQ_IND);
        CASE_RETURN_STRING(eWNI_SME_SET_APWPARSNIEs_REQ);
        CASE_RETURN_STRING(eWNI_SME_UPPER_LAYER_ASSOC_CNF);
        CASE_RETURN_STRING(eWNI_SME_HIDE_SSID_REQ);
        CASE_RETURN_STRING(eWNI_SME_REMAIN_ON_CHANNEL_REQ);
        CASE_RETURN_STRING(eWNI_SME_REMAIN_ON_CHN_IND);
        CASE_RETURN_STRING(eWNI_SME_REMAIN_ON_CHN_RSP);
        CASE_RETURN_STRING(eWNI_SME_MGMT_FRM_IND);
        CASE_RETURN_STRING(eWNI_SME_REMAIN_ON_CHN_RDY_IND);
        CASE_RETURN_STRING(eWNI_SME_SEND_ACTION_FRAME_IND);
        CASE_RETURN_STRING(eWNI_SME_ACTION_FRAME_SEND_CNF);
        CASE_RETURN_STRING(eWNI_SME_ABORT_REMAIN_ON_CHAN_IND);
        CASE_RETURN_STRING(eWNI_SME_UPDATE_NOA);
        CASE_RETURN_STRING(eWNI_SME_CLEAR_DFS_CHANNEL_LIST);
        CASE_RETURN_STRING(eWNI_SME_PRE_CHANNEL_SWITCH_FULL_POWER);
        CASE_RETURN_STRING(eWNI_SME_GET_SNR_REQ);
        CASE_RETURN_STRING(eWNI_PMC_MSG_TYPES_BEGIN);

        //General Power Save Messages
        CASE_RETURN_STRING(eWNI_PMC_PWR_SAVE_CFG);

        //BMPS Messages
        CASE_RETURN_STRING(eWNI_PMC_ENTER_BMPS_REQ);
        CASE_RETURN_STRING(eWNI_PMC_ENTER_BMPS_RSP);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_BMPS_REQ);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_BMPS_RSP);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_BMPS_IND);

        //IMPS Messages.
        CASE_RETURN_STRING(eWNI_PMC_ENTER_IMPS_REQ);
        CASE_RETURN_STRING(eWNI_PMC_ENTER_IMPS_RSP);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_IMPS_REQ);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_IMPS_RSP);

        //UAPSD Messages
        CASE_RETURN_STRING(eWNI_PMC_ENTER_UAPSD_REQ);
        CASE_RETURN_STRING(eWNI_PMC_ENTER_UAPSD_RSP);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_UAPSD_REQ);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_UAPSD_RSP);

        CASE_RETURN_STRING(eWNI_PMC_SMPS_STATE_IND);
        CASE_RETURN_STRING(eWNI_PMC_WOWL_ADD_BCAST_PTRN);
        CASE_RETURN_STRING(eWNI_PMC_WOWL_DEL_BCAST_PTRN);
        CASE_RETURN_STRING(eWNI_PMC_ENTER_WOWL_REQ);
        CASE_RETURN_STRING(eWNI_PMC_ENTER_WOWL_RSP);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_WOWL_REQ);
        CASE_RETURN_STRING(eWNI_PMC_EXIT_WOWL_RSP);

#ifdef WLAN_FEATURE_PACKET_FILTERING
        CASE_RETURN_STRING(eWNI_PMC_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP);
#endif // WLAN_FEATURE_PACKET_FILTERING
#if defined WLAN_FEATURE_VOWIFI
        CASE_RETURN_STRING(eWNI_SME_RRM_MSG_TYPE_BEGIN);
        CASE_RETURN_STRING(eWNI_SME_NEIGHBOR_REPORT_REQ_IND);
        CASE_RETURN_STRING(eWNI_SME_NEIGHBOR_REPORT_IND);
        CASE_RETURN_STRING(eWNI_SME_BEACON_REPORT_REQ_IND);
        CASE_RETURN_STRING(eWNI_SME_BEACON_REPORT_RESP_XMIT_IND);
#endif
        CASE_RETURN_STRING(eWNI_SME_ADD_STA_SELF_REQ);
        CASE_RETURN_STRING(eWNI_SME_ADD_STA_SELF_RSP);
        CASE_RETURN_STRING(eWNI_SME_DEL_STA_SELF_REQ);
        CASE_RETURN_STRING(eWNI_SME_DEL_STA_SELF_RSP);
#if defined WLAN_FEATURE_VOWIFI_11R
        CASE_RETURN_STRING(eWNI_SME_FT_PRE_AUTH_REQ);
        CASE_RETURN_STRING(eWNI_SME_FT_PRE_AUTH_RSP);
        CASE_RETURN_STRING(eWNI_SME_FT_UPDATE_KEY);
        CASE_RETURN_STRING(eWNI_SME_FT_AGGR_QOS_REQ);
        CASE_RETURN_STRING(eWNI_SME_FT_AGGR_QOS_RSP);
#endif
#if defined FEATURE_WLAN_CCX
        CASE_RETURN_STRING(eWNI_SME_CCX_ADJACENT_AP_REPORT);
#endif
        CASE_RETURN_STRING(eWNI_SME_REGISTER_MGMT_FRAME_REQ);
        CASE_RETURN_STRING(eWNI_SME_COEX_IND);
#ifdef FEATURE_WLAN_SCAN_PNO
        CASE_RETURN_STRING(eWNI_SME_PREF_NETWORK_FOUND_IND);
#endif // FEATURE_WLAN_SCAN_PNO
        CASE_RETURN_STRING(eWNI_SME_TX_PER_HIT_IND);
        CASE_RETURN_STRING(eWNI_SME_CHANGE_COUNTRY_CODE);
        CASE_RETURN_STRING(eWNI_SME_GENERIC_CHANGE_COUNTRY_CODE);
        CASE_RETURN_STRING(eWNI_SME_PRE_SWITCH_CHL_IND);
        CASE_RETURN_STRING(eWNI_SME_POST_SWITCH_CHL_IND);
        CASE_RETURN_STRING(eWNI_SME_MAX_ASSOC_EXCEEDED);
        CASE_RETURN_STRING(eWNI_SME_BTAMP_LOG_LINK_IND);//to serialize the create/accpet LL req from HCI
#ifdef WLAN_FEATURE_GTK_OFFLOAD
        CASE_RETURN_STRING(eWNI_PMC_GTK_OFFLOAD_GETINFO_RSP);
#endif // WLAN_FEATURE_GTK_OFFLOAD
#ifdef WLAN_WAKEUP_EVENTS
        CASE_RETURN_STRING(eWNI_SME_WAKE_REASON_IND);
#endif // WLAN_WAKEUP_EVENTS
        CASE_RETURN_STRING(eWNI_SME_EXCLUDE_UNENCRYPTED);
        CASE_RETURN_STRING(eWNI_SME_RSSI_IND); //RSSI indication from TL to be serialized on MC thread
        CASE_RETURN_STRING(eWNI_SME_MSG_TYPES_END);
        CASE_RETURN_STRING(eWNI_SME_GET_ROAM_RSSI_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_ROAM_RSSI_RSP);
        CASE_RETURN_STRING(eWNI_SME_GET_TSM_STATS_REQ);
        CASE_RETURN_STRING(eWNI_SME_GET_TSM_STATS_RSP);
        CASE_RETURN_STRING(eWNI_SME_HT40_OBSS_SCAN_IND);
        CASE_RETURN_STRING(eWNI_SME_HT40_STOP_OBSS_SCAN_IND);
        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}


tANI_U8* macTraceGetWdaMsgString( tANI_U16 wdaMsg )
{
    switch( wdaMsg )
    {
        CASE_RETURN_STRING(WDA_APP_SETUP_NTF);
        CASE_RETURN_STRING(WDA_NIC_OPER_NTF);
        CASE_RETURN_STRING(WDA_INIT_START_REQ);
        CASE_RETURN_STRING(WDA_RESET_REQ);
        CASE_RETURN_STRING(WDA_HDD_ADDBA_REQ);
        CASE_RETURN_STRING(WDA_HDD_ADDBA_RSP);
        CASE_RETURN_STRING(WDA_DELETEBA_IND);
        CASE_RETURN_STRING(WDA_BA_FAIL_IND);
        CASE_RETURN_STRING(WDA_TL_FLUSH_AC_REQ);
        CASE_RETURN_STRING(WDA_TL_FLUSH_AC_RSP);

        CASE_RETURN_STRING(WDA_ITC_MSG_TYPES_BEGIN);
        CASE_RETURN_STRING(WDA_WDT_KAM_RSP);
        CASE_RETURN_STRING(WDA_TIMER_TEMP_MEAS_REQ);
        CASE_RETURN_STRING(WDA_TIMER_PERIODIC_STATS_COLLECT_REQ);
        CASE_RETURN_STRING(WDA_CAL_REQ_NTF);
        CASE_RETURN_STRING(WDA_MNT_OPEN_TPC_TEMP_MEAS_REQ);
        CASE_RETURN_STRING(WDA_CCA_MONITOR_INTERVAL_TO);
        CASE_RETURN_STRING(WDA_CCA_MONITOR_DURATION_TO);
        CASE_RETURN_STRING(WDA_CCA_MONITOR_START);
        CASE_RETURN_STRING(WDA_CCA_MONITOR_STOP);
        CASE_RETURN_STRING(WDA_CCA_CHANGE_MODE);
        CASE_RETURN_STRING(WDA_TIMER_WRAP_AROUND_STATS_COLLECT_REQ);

        CASE_RETURN_STRING(WDA_ADD_STA_REQ);
        CASE_RETURN_STRING(WDA_ADD_STA_RSP);
        CASE_RETURN_STRING(WDA_ADD_STA_SELF_RSP);
        CASE_RETURN_STRING(WDA_DEL_STA_SELF_RSP);
        CASE_RETURN_STRING(WDA_DELETE_STA_REQ);
        CASE_RETURN_STRING(WDA_DELETE_STA_RSP);
        CASE_RETURN_STRING(WDA_ADD_BSS_REQ);
        CASE_RETURN_STRING(WDA_ADD_BSS_RSP);
        CASE_RETURN_STRING(WDA_DELETE_BSS_REQ);
        CASE_RETURN_STRING(WDA_DELETE_BSS_RSP);
        CASE_RETURN_STRING(WDA_INIT_SCAN_REQ);
        CASE_RETURN_STRING(WDA_INIT_SCAN_RSP);
        CASE_RETURN_STRING(WDA_START_SCAN_REQ);
        CASE_RETURN_STRING(WDA_START_SCAN_RSP);
        CASE_RETURN_STRING(WDA_END_SCAN_REQ);
        CASE_RETURN_STRING(WDA_END_SCAN_RSP);
        CASE_RETURN_STRING(WDA_FINISH_SCAN_REQ);
        CASE_RETURN_STRING(WDA_FINISH_SCAN_RSP);
        CASE_RETURN_STRING(WDA_SEND_BEACON_REQ);
        CASE_RETURN_STRING(WDA_SEND_BEACON_RSP);

        CASE_RETURN_STRING(WDA_INIT_CFG_REQ);
        CASE_RETURN_STRING(WDA_INIT_CFG_RSP);

        CASE_RETURN_STRING(WDA_INIT_WM_CFG_REQ);
        CASE_RETURN_STRING(WDA_INIT_WM_CFG_RSP);

        CASE_RETURN_STRING(WDA_SET_BSSKEY_REQ);
        CASE_RETURN_STRING(WDA_SET_BSSKEY_RSP);
        CASE_RETURN_STRING(WDA_SET_STAKEY_REQ);
        CASE_RETURN_STRING(WDA_SET_STAKEY_RSP);
        CASE_RETURN_STRING(WDA_DPU_STATS_REQ);
        CASE_RETURN_STRING(WDA_DPU_STATS_RSP);
        CASE_RETURN_STRING(WDA_GET_DPUINFO_REQ);
        CASE_RETURN_STRING(WDA_GET_DPUINFO_RSP);

        CASE_RETURN_STRING(WDA_UPDATE_EDCA_PROFILE_IND);

        CASE_RETURN_STRING(WDA_UPDATE_STARATEINFO_REQ);
        CASE_RETURN_STRING(WDA_UPDATE_STARATEINFO_RSP);

        CASE_RETURN_STRING(WDA_UPDATE_BEACON_IND);
        CASE_RETURN_STRING(WDA_UPDATE_CF_IND);
        CASE_RETURN_STRING(WDA_CHNL_SWITCH_REQ);
        CASE_RETURN_STRING(WDA_ADD_TS_REQ);
        CASE_RETURN_STRING(WDA_DEL_TS_REQ);
        CASE_RETURN_STRING(WDA_SOFTMAC_TXSTAT_REPORT);
        CASE_RETURN_STRING(WDA_MBOX_SENDMSG_COMPLETE_IND);
        CASE_RETURN_STRING(WDA_EXIT_BMPS_REQ);
        CASE_RETURN_STRING(WDA_EXIT_BMPS_RSP);
        CASE_RETURN_STRING(WDA_EXIT_BMPS_IND);
        CASE_RETURN_STRING(WDA_ENTER_BMPS_REQ);
        CASE_RETURN_STRING(WDA_ENTER_BMPS_RSP);
        CASE_RETURN_STRING(WDA_BMPS_STATUS_IND);
        CASE_RETURN_STRING(WDA_MISSED_BEACON_IND);

        CASE_RETURN_STRING(WDA_CFG_RXP_FILTER_REQ);
        CASE_RETURN_STRING(WDA_CFG_RXP_FILTER_RSP);
        CASE_RETURN_STRING(WDA_SWITCH_CHANNEL_RSP);
        CASE_RETURN_STRING(WDA_P2P_NOA_ATTR_IND);
        CASE_RETURN_STRING(WDA_P2P_NOA_START_IND);
        CASE_RETURN_STRING(WDA_PWR_SAVE_CFG);

        CASE_RETURN_STRING(WDA_REGISTER_PE_CALLBACK);
        CASE_RETURN_STRING(WDA_SOFTMAC_MEM_READREQUEST);
        CASE_RETURN_STRING(WDA_SOFTMAC_MEM_WRITEREQUEST);

        CASE_RETURN_STRING(WDA_SOFTMAC_MEM_READRESPONSE);
        CASE_RETURN_STRING(WDA_SOFTMAC_BULKREGWRITE_CONFIRM);
        CASE_RETURN_STRING(WDA_SOFTMAC_BULKREGREAD_RESPONSE);
        CASE_RETURN_STRING(WDA_SOFTMAC_HOSTMESG_MSGPROCESSRESULT);

        CASE_RETURN_STRING(WDA_ADDBA_REQ);
        CASE_RETURN_STRING(WDA_ADDBA_RSP);
        CASE_RETURN_STRING(WDA_DELBA_IND);
        CASE_RETURN_STRING(WDA_DEL_BA_IND);
        CASE_RETURN_STRING(WDA_MIC_FAILURE_IND);

        CASE_RETURN_STRING(WDA_DELBA_REQ);
        CASE_RETURN_STRING(WDA_IBSS_STA_ADD);
        CASE_RETURN_STRING(WDA_TIMER_ADJUST_ADAPTIVE_THRESHOLD_IND);
        CASE_RETURN_STRING(WDA_SET_LINK_STATE);
        CASE_RETURN_STRING(WDA_SET_LINK_STATE_RSP);
        CASE_RETURN_STRING(WDA_ENTER_IMPS_REQ);
        CASE_RETURN_STRING(WDA_ENTER_IMPS_RSP);
        CASE_RETURN_STRING(WDA_EXIT_IMPS_RSP);
        CASE_RETURN_STRING(WDA_EXIT_IMPS_REQ);
        CASE_RETURN_STRING(WDA_SOFTMAC_HOSTMESG_PS_STATUS_IND);
        CASE_RETURN_STRING(WDA_POSTPONE_ENTER_IMPS_RSP);
        CASE_RETURN_STRING(WDA_STA_STAT_REQ);
        CASE_RETURN_STRING(WDA_GLOBAL_STAT_REQ);
        CASE_RETURN_STRING(WDA_AGGR_STAT_REQ);
        CASE_RETURN_STRING(WDA_STA_STAT_RSP);
        CASE_RETURN_STRING(WDA_GLOBAL_STAT_RSP);
        CASE_RETURN_STRING(WDA_AGGR_STAT_RSP);
        CASE_RETURN_STRING(WDA_STAT_SUMM_REQ);
        CASE_RETURN_STRING(WDA_STAT_SUMM_RSP);
        CASE_RETURN_STRING(WDA_REMOVE_BSSKEY_REQ);
        CASE_RETURN_STRING(WDA_REMOVE_BSSKEY_RSP);
        CASE_RETURN_STRING(WDA_REMOVE_STAKEY_REQ);
        CASE_RETURN_STRING(WDA_REMOVE_STAKEY_RSP);
        CASE_RETURN_STRING(WDA_SET_STA_BCASTKEY_REQ);
        CASE_RETURN_STRING(WDA_SET_STA_BCASTKEY_RSP);
        CASE_RETURN_STRING(WDA_REMOVE_STA_BCASTKEY_REQ);
        CASE_RETURN_STRING(WDA_REMOVE_STA_BCASTKEY_RSP);
        CASE_RETURN_STRING(WDA_ADD_TS_RSP);
        CASE_RETURN_STRING(WDA_DPU_MIC_ERROR);

        CASE_RETURN_STRING(WDA_TIMER_BA_ACTIVITY_REQ);
        CASE_RETURN_STRING(WDA_TIMER_CHIP_MONITOR_TIMEOUT);
        CASE_RETURN_STRING(WDA_TIMER_TRAFFIC_ACTIVITY_REQ);
        CASE_RETURN_STRING(WDA_TIMER_ADC_RSSI_STATS);
#ifdef FEATURE_WLAN_CCX
        CASE_RETURN_STRING(WDA_TSM_STATS_REQ);
        CASE_RETURN_STRING(WDA_TSM_STATS_RSP);
#endif
        CASE_RETURN_STRING(WDA_UPDATE_UAPSD_IND);
        CASE_RETURN_STRING(WDA_SET_MIMOPS_REQ);
        CASE_RETURN_STRING(WDA_SET_MIMOPS_RSP);
        CASE_RETURN_STRING(WDA_SYS_READY_IND );
        CASE_RETURN_STRING(WDA_SET_TX_POWER_REQ);
        CASE_RETURN_STRING(WDA_SET_TX_POWER_RSP);
        CASE_RETURN_STRING(WDA_GET_TX_POWER_REQ);
        CASE_RETURN_STRING(WDA_GET_TX_POWER_RSP);
        CASE_RETURN_STRING(WDA_GET_NOISE_REQ );
        CASE_RETURN_STRING(WDA_GET_NOISE_RSP);
        CASE_RETURN_STRING(WDA_SET_TX_PER_TRACKING_REQ);

        CASE_RETURN_STRING(WDA_TRANSMISSION_CONTROL_IND);
        CASE_RETURN_STRING(WDA_INIT_RADAR_IND);

        CASE_RETURN_STRING(WDA_BEACON_PRE_IND );
        CASE_RETURN_STRING(WDA_ENTER_UAPSD_REQ);
        CASE_RETURN_STRING(WDA_ENTER_UAPSD_RSP);
        CASE_RETURN_STRING(WDA_EXIT_UAPSD_REQ  );
        CASE_RETURN_STRING(WDA_EXIT_UAPSD_RSP );
        CASE_RETURN_STRING(WDA_LOW_RSSI_IND   );
        CASE_RETURN_STRING(WDA_BEACON_FILTER_IND);
        CASE_RETURN_STRING(WDA_WOWL_ADD_BCAST_PTRN);
        CASE_RETURN_STRING(WDA_WOWL_DEL_BCAST_PTRN);
        CASE_RETURN_STRING(WDA_WOWL_ENTER_REQ);
        CASE_RETURN_STRING(WDA_WOWL_ENTER_RSP);
        CASE_RETURN_STRING(WDA_WOWL_EXIT_REQ );
        CASE_RETURN_STRING(WDA_WOWL_EXIT_RSP );
        CASE_RETURN_STRING(WDA_TX_COMPLETE_IND);
        CASE_RETURN_STRING(WDA_TIMER_RA_COLLECT_AND_ADAPT);
        CASE_RETURN_STRING(WDA_GET_STATISTICS_REQ);
        CASE_RETURN_STRING(WDA_GET_STATISTICS_RSP);
        CASE_RETURN_STRING(WDA_SET_KEY_DONE);

        CASE_RETURN_STRING(WDA_BTC_SET_CFG);
        CASE_RETURN_STRING(WDA_SIGNAL_BT_EVENT);
        CASE_RETURN_STRING(WDA_HANDLE_FW_MBOX_RSP);
        CASE_RETURN_STRING(WDA_UPDATE_PROBE_RSP_TEMPLATE_IND);
        CASE_RETURN_STRING(WDA_SIGNAL_BTAMP_EVENT);
#ifdef FEATURE_OEM_DATA_SUPPORT
        CASE_RETURN_STRING(WDA_START_OEM_DATA_REQ );
        CASE_RETURN_STRING(WDA_START_OEM_DATA_RSP);
        CASE_RETURN_STRING(WDA_FINISH_OEM_DATA_REQ);
#endif //SUPPORT_BEACON_FILTER
        CASE_RETURN_STRING(WDA_SET_MAX_TX_POWER_REQ);
        CASE_RETURN_STRING(WDA_SET_MAX_TX_POWER_RSP);
        CASE_RETURN_STRING(WDA_SEND_MSG_COMPLETE);
        CASE_RETURN_STRING(WDA_SET_HOST_OFFLOAD);
        CASE_RETURN_STRING(WDA_SET_KEEP_ALIVE);
#ifdef WLAN_NS_OFFLOAD
        CASE_RETURN_STRING(WDA_SET_NS_OFFLOAD);
#endif //WLAN_NS_OFFLOAD
        CASE_RETURN_STRING(WDA_ADD_STA_SELF_REQ);
        CASE_RETURN_STRING(WDA_DEL_STA_SELF_REQ);
        CASE_RETURN_STRING(WDA_SET_P2P_GO_NOA_REQ);
        CASE_RETURN_STRING(WDA_TX_COMPLETE_TIMEOUT_IND);
        CASE_RETURN_STRING(WDA_WLAN_SUSPEND_IND);
        CASE_RETURN_STRING(WDA_WLAN_RESUME_REQ);
        CASE_RETURN_STRING(WDA_MSG_TYPES_END);
        CASE_RETURN_STRING(WDA_MMH_TXMB_READY_EVT);
        CASE_RETURN_STRING(WDA_MMH_RXMB_DONE_EVT);
        CASE_RETURN_STRING(WDA_MMH_MSGQ_NE_EVT);
#ifdef WLAN_FEATURE_VOWIFI_11R
        CASE_RETURN_STRING(WDA_AGGR_QOS_REQ);
        CASE_RETURN_STRING(WDA_AGGR_QOS_RSP);
#endif /* WLAN_FEATURE_VOWIFI_11R */
        CASE_RETURN_STRING(WDA_FTM_CMD_REQ);
        CASE_RETURN_STRING(WDA_FTM_CMD_RSP);
#ifdef FEATURE_WLAN_SCAN_PNO
        CASE_RETURN_STRING(WDA_SET_PNO_REQ);
        CASE_RETURN_STRING(WDA_SET_RSSI_FILTER_REQ);
        CASE_RETURN_STRING(WDA_UPDATE_SCAN_PARAMS_REQ);
        CASE_RETURN_STRING(WDA_SET_PNO_CHANGED_IND);
#endif // FEATURE_WLAN_SCAN_PNO
#ifdef WLAN_FEATURE_ROAM_SCAN_OFFLOAD
        CASE_RETURN_STRING(WDA_ROAM_SCAN_OFFLOAD_REQ);
#endif
#ifdef WLAN_WAKEUP_EVENTS
        CASE_RETURN_STRING(WDA_WAKE_REASON_IND);
#endif // WLAN_WAKEUP_EVENTS
#ifdef WLAN_FEATURE_PACKET_FILTERING
        CASE_RETURN_STRING(WDA_8023_MULTICAST_LIST_REQ);
        CASE_RETURN_STRING(WDA_RECEIVE_FILTER_SET_FILTER_REQ);
        CASE_RETURN_STRING(WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_REQ);
        CASE_RETURN_STRING(WDA_PACKET_COALESCING_FILTER_MATCH_COUNT_RSP);
        CASE_RETURN_STRING(WDA_RECEIVE_FILTER_CLEAR_FILTER_REQ);
#endif // WLAN_FEATURE_PACKET_FILTERING
        CASE_RETURN_STRING(WDA_SET_POWER_PARAMS_REQ);
#ifdef WLAN_FEATURE_GTK_OFFLOAD
        CASE_RETURN_STRING(WDA_GTK_OFFLOAD_REQ);
        CASE_RETURN_STRING(WDA_GTK_OFFLOAD_GETINFO_REQ);
        CASE_RETURN_STRING(WDA_GTK_OFFLOAD_GETINFO_RSP);
#endif //WLAN_FEATURE_GTK_OFFLOAD
        CASE_RETURN_STRING(WDA_SET_TM_LEVEL_REQ);
#ifdef WLAN_FEATURE_11AC
        CASE_RETURN_STRING(WDA_UPDATE_OP_MODE);
#endif
#ifdef FEATURE_WLAN_BATCH_SCAN
        CASE_RETURN_STRING(WDA_SET_BATCH_SCAN_REQ);
        CASE_RETURN_STRING(WDA_TRIGGER_BATCH_SCAN_RESULT_IND);
#endif
        default:
            return((tANI_U8*) "UNKNOWN" );
            break;
    }
}

tANI_U8* macTraceGetLimMsgString( tANI_U16 limMsg )
{
    switch( limMsg )
    {
        CASE_RETURN_STRING(SIR_LIM_RETRY_INTERRUPT_MSG);
        CASE_RETURN_STRING(SIR_BB_XPORT_MGMT_MSG );
        CASE_RETURN_STRING(SIR_LIM_INV_KEY_INTERRUPT_MSG );
        CASE_RETURN_STRING(SIR_LIM_KEY_ID_INTERRUPT_MSG );
        CASE_RETURN_STRING(SIR_LIM_REPLAY_THRES_INTERRUPT_MSG );
        CASE_RETURN_STRING(SIR_LIM_TD_DUMMY_CALLBACK_MSG );
        CASE_RETURN_STRING(SIR_LIM_SCH_CLEAN_MSG  );
        CASE_RETURN_STRING(SIR_LIM_RADAR_DETECT_IND);
        CASE_RETURN_STRING(SIR_LIM_DEL_TS_IND);
        CASE_RETURN_STRING(SIR_LIM_ADD_BA_IND );
        CASE_RETURN_STRING(SIR_LIM_DEL_BA_ALL_IND);
        CASE_RETURN_STRING(SIR_LIM_DELETE_STA_CONTEXT_IND);
        CASE_RETURN_STRING(SIR_LIM_DEL_BA_IND );
        CASE_RETURN_STRING(SIR_LIM_UPDATE_BEACON);
        CASE_RETURN_STRING(SIR_LIM_MIN_CHANNEL_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_MAX_CHANNEL_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_JOIN_FAIL_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_AUTH_FAIL_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_AUTH_RSP_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_ASSOC_FAIL_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_REASSOC_FAIL_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_HEART_BEAT_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_CHANNEL_SCAN_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_PROBE_HB_FAILURE_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_ADDTS_RSP_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_LINK_TEST_DURATION_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_HASH_MISS_THRES_TIMEOUT  );
        CASE_RETURN_STRING(SIR_LIM_CNF_WAIT_TIMEOUT         );
        CASE_RETURN_STRING(SIR_LIM_KEEPALIVE_TIMEOUT        );
        CASE_RETURN_STRING(SIR_LIM_UPDATE_OLBC_CACHEL_TIMEOUT );
        CASE_RETURN_STRING(SIR_LIM_CHANNEL_SWITCH_TIMEOUT   );
        CASE_RETURN_STRING(SIR_LIM_QUIET_TIMEOUT            );
        CASE_RETURN_STRING(SIR_LIM_QUIET_BSS_TIMEOUT      );
        CASE_RETURN_STRING(SIR_LIM_WPS_OVERLAP_TIMEOUT);
#ifdef WLAN_FEATURE_VOWIFI_11R
        CASE_RETURN_STRING(SIR_LIM_FT_PREAUTH_RSP_TIMEOUT);
#endif
        CASE_RETURN_STRING(SIR_LIM_REMAIN_CHN_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_INSERT_SINGLESHOT_NOA_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_CONVERT_ACTIVE_CHANNEL_TO_PASSIVE);
#ifdef WMM_APSD
        CASE_RETURN_STRING(SIR_LIM_WMM_APSD_SP_START_MSG_TYPE );
        CASE_RETURN_STRING(SIR_LIM_WMM_APSD_SP_END_MSG_TYPE );
#endif
        CASE_RETURN_STRING(SIR_LIM_BEACON_GEN_IND );
        CASE_RETURN_STRING(SIR_LIM_PERIODIC_PROBE_REQ_TIMEOUT);
#ifdef FEATURE_WLAN_CCX
        CASE_RETURN_STRING(SIR_LIM_CCX_TSM_TIMEOUT);
#endif
        CASE_RETURN_STRING(SIR_LIM_DISASSOC_ACK_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_DEAUTH_ACK_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_PERIODIC_JOIN_PROBE_REQ_TIMEOUT);
        CASE_RETURN_STRING(SIR_LIM_MSG_TYPES_END);

        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

tANI_U8* macTraceGetCfgMsgString( tANI_U16 cfgMsg )
{
    switch( cfgMsg )
    {
        CASE_RETURN_STRING(WNI_CFG_PARAM_UPDATE_IND);
        CASE_RETURN_STRING(WNI_CFG_DNLD_REQ);
        CASE_RETURN_STRING(WNI_CFG_DNLD_CNF);
        CASE_RETURN_STRING(WNI_CFG_GET_RSP);
        CASE_RETURN_STRING(WNI_CFG_SET_CNF);
        CASE_RETURN_STRING(SIR_CFG_PARAM_UPDATE_IND);
        CASE_RETURN_STRING(SIR_CFG_DOWNLOAD_COMPLETE_IND);

        CASE_RETURN_STRING(WNI_CFG_SET_REQ_NO_RSP);
        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

tANI_U8* macTraceGetInfoLogString( tANI_U16 infoLog )
{
    switch( infoLog )
    {
        CASE_RETURN_STRING(eLOG_NODROP_MISSED_BEACON_SCENARIO);
        CASE_RETURN_STRING(eLOG_PROC_DEAUTH_FRAME_SCENARIO);
        default:
            return( (tANI_U8*)"UNKNOWN" );
            break;
    }
}

tANI_U8* macTraceGetModuleString( tANI_U8 moduleId  )
{
    return ((tANI_U8*)"PE");
    //return gVosTraceInfo[moduleId].moduleNameStr;
}

void macTraceReset(tpAniSirGlobal pMac)
{
}

void macTrace(tpAniSirGlobal pMac,  tANI_U8 code, tANI_U8 session, tANI_U32 data)
{
    //Today macTrace is being invoked by PE only, need to remove this function once PE is migrated to using new trace API.
    macTraceNew(pMac, VOS_MODULE_ID_PE, code, session, data);
}

void macTraceNew(tpAniSirGlobal pMac, tANI_U8 module, tANI_U8 code, tANI_U8 session, tANI_U32 data)
{
    vos_trace(module, code, session, data);
}

tANI_U8* macTraceMsgString(tpAniSirGlobal pMac, tANI_U32 msgType)
{
    tANI_U16 msgId = (tANI_U16)MAC_TRACE_GET_MSG_ID(msgType);
    tANI_U8 moduleId = (tANI_U8)MAC_TRACE_GET_MODULE_ID(msgType);

    switch(moduleId)
    {
        case SIR_LIM_MODULE_ID:
            if(msgId >= SIR_LIM_ITC_MSG_TYPES_BEGIN)
                return macTraceGetLimMsgString((tANI_U16)msgType);
            else
                return macTraceGetSmeMsgString((tANI_U16)msgType);
            break;
        case SIR_WDA_MODULE_ID:
                return macTraceGetWdaMsgString((tANI_U16)msgType);
        case SIR_CFG_MODULE_ID:
                return macTraceGetCfgMsgString((tANI_U16)msgType);
        default:
                return ((tANI_U8*)"Unknown MsgType");
    }
}

#endif
