using System;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.CodeDom.Compiler;
using Microsoft.CSharp;
using System.Reflection;
using SiriusConfigurator.DataLayer;
using SiriusConfigurator.StatusHandler;
using System.Xml.Linq;
using System.Linq;
using SRXml = SiriusConfigurator.BusinessLayer.BEntities.Xml;

namespace SiriusConfigurator
{
    public class ScriptClass
    {
		DL_Component siriusApp = new DL_Component();
		bool ValidationsStatus = false;
		List<NodeExt> TimeServGeneralConfig;
		List<NodeExt> TimeServ16BitsSoftwareTimer;
		List<NodeExt> TimeServ32BitsSoftwareTimer;
		List<NodeExt> TimeServ_SlowTimer_1ms;
		string Uc_Used;
		string FTM_ModuleIndex;
		string Predefined_Timer;
		
		public ScriptClass()
		{
			TimeServGeneralConfig = siriusApp.GetNode("TimeServGeneral");
			TimeServ16BitsSoftwareTimer = siriusApp.GetNode("TimeServ_16BitsSoftwareTimer");
			TimeServ32BitsSoftwareTimer = siriusApp.GetNode("TimeServ_32BitsSoftwareTimer");
			TimeServ_SlowTimer_1ms = siriusApp.GetNode("TimeServ_SlowTimer_1ms");
			Uc_Used = TimeServGeneralConfig[0].GetAttribute("Uc_Used");
			Predefined_Timer = TimeServGeneralConfig[0].GetAttribute("Predefined_Timer");

		}
		
		public string Dynamic(NodeExt node, SRXml.AttributesXml attribute)
	    {
			if ((node.Name == "TimeServGeneral") && (attribute.Attribute == "Uc_Used") && (attribute.Value != "S32K"))
			{
				SRXml.AttributesXml ModuleIndex = node.Attributes.Find(x => x.Attribute == "FTM_ModuleIndex");
				siriusApp.SetValueOfAttribute(node, ModuleIndex, "");
				siriusApp.SetEnable(node, ModuleIndex, false);
			}
			
			if ((node.Name == "TimeServGeneral") && (attribute.Attribute == "Uc_Used") && (attribute.Value == "S32K"))
			{
				SRXml.AttributesXml ModuleIndex = node.Attributes.Find(x => x.Attribute == "FTM_ModuleIndex");
				siriusApp.SetEnable(node, ModuleIndex, true);
			}
			
            return "OK";
	    }
        public string Validate()
        {
			string RetValue = "ERROR";

            /* Validation of Time Service configurations.  */
            ValidateTimeServDriver();

            /* Check if the validation was successful. */
            if (ValidationsStatus == false)
            {
                /* Validation was successful make sure we return the OK value. */
                RetValue = "OK";
            }
            else
            {
                /* There was an error in validation, display the proper message. */
                MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "Time Service configuration is not valid.");
            }

            return RetValue;
        }
		/* ------------------------------------------------------------------------ VALIDATION ------------------------------------------------------------------------ */

        /* Private method used to check the timers' parameters validity  */
        private void ValidateTimeServDriver()
        {
			String Name;
			string RetValue = "OK";
			FTM_ModuleIndex = TimeServGeneralConfig[0].GetAttribute("FTM_ModuleIndex");

			/* check if 16bit software timers were configured */
			if (TimeServ16BitsSoftwareTimer.Count != 0) 	
			{
				for (int index = 0; index < TimeServ16BitsSoftwareTimer.Count; index++ )
				{
					Name = TimeServ16BitsSoftwareTimer[index].GetAttribute("SoftwareTimer_Name");
					if( Name.Length <  1)
					/* The name block is empty or the characters introduced by the user are invalid. */
					throwError("The TimeService SoftwareTimer_Name is invalid, it is shorter than 1 characters or it contains special symbols. The value must be a variable's name.");
				}
			}
			/* check if 32bit software timers were configured */
			if (TimeServ32BitsSoftwareTimer.Count != 0) 	
			{
				for (int index = 0; index < TimeServ32BitsSoftwareTimer.Count; index++ )
				{
					Name = TimeServ32BitsSoftwareTimer[index].GetAttribute("SoftwareTimer_Name");
					if( Name.Length <  1)
					throwError("The TimeService SoftwareTimer_Name is invalid, it is shorter than 1 characters or it contains special symbols. The value must be a variable's name.");
				}
			}
			if (TimeServ_SlowTimer_1ms.Count != 0) 	
			{
				for (int index = 0; index < TimeServ_SlowTimer_1ms.Count; index++ )
				{
					Name = TimeServ_SlowTimer_1ms[index].GetAttribute("SoftwareTimer_Name");
					if( Name.Length <  1)
					/* The name block is empty or the characters introduced by the user are invalid. */
					throwError("The TimeService SoftwareTimer_Name is invalid, it is shorter than 1 characters or it contains special symbols. The value must be a variable's name.");
				}
			}
			
			if (Uc_Used == "RL78")
			{
				NodeExt ChannelNode = siriusApp.GetNode("GptChannel").Find(x => x.GetAttribute("ChannelName") == Predefined_Timer);
				if (ChannelNode == null)
				{
					throwError("Could not find GptChannel in Sirius for RL78 configuration. The GPT predef timer interrupt flag cannot be generated correctly.");
				}
			}	
			if ((Uc_Used == "S32K") && (FTM_ModuleIndex.Length == 0))
			{
				throwError("When S32K is used, please set the FTM module index (0..7) in TimeServGeneral->FTM_ModuleIndex");		
			}				
		}
		/* ------------------------------------------------------------------------ END OF VALIDATION ------------------------------------------------------------------------ */
		/* Method used to throw an error in case the validation was not successfull. */
        void throwError(string errorMessage)
        {
            MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, errorMessage);
            ValidationsStatus = true;
        }
		
        /* --------------------------------------------------- Header and Footer strings used in file generation ---------------------------------------- */

        /* ------------------------------ C File ---------------------------- */
    string FILE_HEADER_TimeService_Cfg = @"/*                                                           
 ******************************************************************************
 *
 * \par Module Owner:
 *   Huf H&uuml;lsbeck & F&uuml;rst GmbH & Co. KG \n
 *   Steeger Str. 17 \n
 *   42551 Velbert \n
 *   Department PDE-S
 *
 ******************************************************************************
 * \par Description:
 * Generated configuration file for TimeService
 * Implementation based on Huf BSW specifications  \n
 *
 * %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *
 *  CM Item:   %PID:%
 *  Itemname:  %PM:%
 *  Location:  %ARCHIVE:%
 *  Revision:  %PR:%
 *  Date:      %DATE:%
 *  Author:    %AUTHOR:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 *
 ******************************************************************************/";

       string FILE_FOOTER_TimeService_Cfg = @"/* %PCMS_HEADER_SUBSTITUTION_START:%
 ******************************************************************************
 * Document Management Information Log (generated by Dimensions CM)
 *
 *  Description:
 *  %PD:%
 *
 *  Used by Baselines:
 *  %PIRB:%
 *
 *  Used by Dimensions CM Projects:
 *  %PIRW:%
 *
 *  Change History:
 *  %PL:%
 *
 * %PCMS_HEADER_SUBSTITUTION_END:%
 */";
 
		StringBuilder HGenerationStream;
		
		private void AddFileHeader_TimeService_Cfg()
		{
			HGenerationStream.Append (FILE_HEADER_TimeService_Cfg);
			HGenerationStream.AppendLine();
		}
		
		private void CompleteFile_TimeService_Cfg()
		{
			string path = @"..\GenFiles\Source\TimeService_Cfg.h";
			System.IO.File.WriteAllText(path, HGenerationStream.ToString());
		}
		private string IntFlag = "";
		private string IntFlagClear = "";

        private void CalculateIntMask(string Gpt_TimerName)
        {
			if (Uc_Used == "RL78")
			{
				NodeExt ChannelNode = siriusApp.GetNode("GptChannel").Find(x => x.GetAttribute("ChannelName") == Gpt_TimerName);
				switch (ChannelNode.GetAttribute("AlocatedHwTimer"))
				{
					case "GPT_CH00":
						IntFlag = "TMIF00";					
						break;
					case "GPT_CH01":
						IntFlag = "TMIF01";
						break;
					case "GPT_CH02":
						IntFlag = "TMIF02";
						break;
					case "GPT_CH03":
						IntFlag = "TMIF03";
						break;
					case "GPT_CH04":
						IntFlag = "TMIF04";
						break;
					case "GPT_CH05":
						IntFlag = "TMIF05";
						break;
					case "GPT_CH06":
						IntFlag = "TMIF06";
						break;
					case "GPT_CH07":
						IntFlag = "TMIF07";
						break;
					case "GPT_CH10":
						IntFlag = "TMIF10";
						break;
					case "GPT_CH11":
						IntFlag = "TMIF11";
						break;
					case "GPT_CH12":
						IntFlag = "TMIF12";
						break;
					case "GPT_CH13":
						IntFlag = "TMIF13";
						break;
					case "GPT_CH14":
						IntFlag = "TMIF14";
						break;
					case "GPT_CH15":
						IntFlag = "TMIF15";
						break;
					case "GPT_CH16":
						IntFlag = "TMIF16";
						break;
					case "GPT_CH17":
						IntFlag = "TMIF17";
						break;
					default:
						break;
				}
				IntFlagClear = "TM_TIMER_INT = 0u";
			}
			if (Uc_Used == "S32K")
			{
				FTM_ModuleIndex = TimeServGeneralConfig[0].GetAttribute("FTM_ModuleIndex");
				IntFlag = "REG_BIT_GET32(FTM_SC_ADDR32("+FTM_ModuleIndex+"), FTM_SC_TOF_MASK_U32)";
				IntFlagClear = "REG_BIT_CLEAR32(FTM_SC_ADDR32("+FTM_ModuleIndex+"), FTM_SC_TOF_MASK_U32)";
			}

      
        }
		private void Generate_TimeService_Cfg()
		{
			HGenerationStream = new StringBuilder();

			string Name;
			AddFileHeader_TimeService_Cfg();
			
			HGenerationStream.AppendLine("#ifndef TIME_SERVICE_CFG_H"+ "\t\t" +"/* To avoid double inclusion */");
			HGenerationStream.AppendLine("#define TIME_SERVICE_CFG_H");
			HGenerationStream.AppendLine("");
			
			HGenerationStream.AppendLine("#include \"Std_Types.h\"");
			HGenerationStream.AppendLine("#include \"Gpt.h\"");
			HGenerationStream.AppendLine("");
			HGenerationStream.AppendLine("/* TimeServGeneral */");
			HGenerationStream.AppendLine("/* Data types depend on the uc used */");
			if (Uc_Used == "RL78")
			{
				HGenerationStream.AppendLine("typedef Gpt_ChannelType Tm_PredefTimerType;");
				HGenerationStream.AppendLine("typedef U16 Tm_PredefTimerRefTimeType;");
			}
			if (Uc_Used == "S32K")
			{
				HGenerationStream.AppendLine("typedef Gpt_PredefTimerType Tm_PredefTimerType;");
				HGenerationStream.AppendLine("typedef U32 Tm_PredefTimerRefTimeType;");
			}
			HGenerationStream.AppendLine("");
			HGenerationStream.AppendLine("/* Define the macro used to address the predefined free-running timer of 1us from GPT */");
			HGenerationStream.AppendLine("#define PREDEFINED_TIMER" + "\t\t" + Predefined_Timer);
			CalculateIntMask(Predefined_Timer);
			HGenerationStream.AppendLine("");
            HGenerationStream.AppendLine("/* Define the macro used to address the interrupt flag of the predefined free-running timer of 1us from GPT  */");
			
			HGenerationStream.AppendLine("#define TM_TIMER_INT\t\t\t\t\t\t\t" + IntFlag);
			HGenerationStream.AppendLine("#define TM_CLEAR_TIMER_PENDING_INT\t\t" + IntFlagClear);

			HGenerationStream.AppendLine("");
            HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:2.5 [Not a defect:Unset] \"The macros can be used when integrating the module\" */");
			
			if (TimeServ16BitsSoftwareTimer.Count != 0) 	
			{
				HGenerationStream.AppendLine("/* The list of 16bits software timers configured by the user */");
				for (int index = 0; index < TimeServ16BitsSoftwareTimer.Count; index++ )
				{
					Name = TimeServ16BitsSoftwareTimer[index].GetAttribute("SoftwareTimer_Name");
					HGenerationStream.AppendLine("#define "+Name+"\t\t"+index+"u");
				}
				HGenerationStream.AppendLine("#define NO_OF_16BIT_SWT_U8"+"\t\t"+TimeServ16BitsSoftwareTimer.Count+"u");
				HGenerationStream.AppendLine("#define TM_16BIT_TIMER_ENABLE"+"\t\t"+"STD_ON");
				
			}
			else 
			{
				HGenerationStream.AppendLine("#define TM_16BIT_TIMER_ENABLE"+"\t\t"+"STD_OFF");
			}
			HGenerationStream.AppendLine("");
			if (TimeServ32BitsSoftwareTimer.Count != 0) 	
			{
				HGenerationStream.AppendLine("/* The list of 32bits software timers configured by the user */");
				for (int index = 0; index < TimeServ32BitsSoftwareTimer.Count; index++ )
				{
					Name = TimeServ32BitsSoftwareTimer[index].GetAttribute("SoftwareTimer_Name");
					HGenerationStream.AppendLine("#define "+Name+"\t\t"+index+"u");
				}
				HGenerationStream.AppendLine("#define NO_OF_32BIT_SWT_U8"+"\t\t"+TimeServ32BitsSoftwareTimer.Count+"u");
				HGenerationStream.AppendLine("#define TM_32BIT_TIMER_ENABLE"+"\t\t"+"STD_ON");
			}
			else
			{
				HGenerationStream.AppendLine("#define TM_32BIT_TIMER_ENABLE"+"\t\t"+"STD_OFF");
			}
            HGenerationStream.AppendLine("");
			if (TimeServ_SlowTimer_1ms.Count != 0) 	
			{
				HGenerationStream.AppendLine("/* The list of 32bits software timers configured by the user */");
				for (int index = 0; index < TimeServ_SlowTimer_1ms.Count; index++ )
				{
					Name = TimeServ_SlowTimer_1ms[index].GetAttribute("SoftwareTimer_Name");
					HGenerationStream.AppendLine("#define "+Name+"\t\t"+index+"u");
				}
				HGenerationStream.AppendLine("#define NO_OF_SLOW_SWT_U8"+"\t\t"+TimeServ_SlowTimer_1ms.Count+"u");
				HGenerationStream.AppendLine("#define TM_SLOW_TIMER_ENABLE"+"\t\t"+"STD_ON");
			}
			else
			{
				HGenerationStream.AppendLine("#define TM_SLOW_TIMER_ENABLE"+"\t\t"+"STD_OFF");
			}
			HGenerationStream.AppendLine("/* polyspace-end MISRA-C3:2.5 [Not a defect:Unset] \"The macros can be used when integrating the module\" */");

            HGenerationStream.AppendLine("");
			
            HGenerationStream.AppendLine("#endif /* TIME_SERVICE_CFG_H */");
			HGenerationStream.AppendLine("");
			HGenerationStream.Append (FILE_FOOTER_TimeService_Cfg);
			
		    CompleteFile_TimeService_Cfg();
			
		
		}
		
		
		public string Generate()
        {
            string RetValue = "OK";
			Generate_TimeService_Cfg();
			
            return RetValue;
        } 
    }
}