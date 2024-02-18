using System;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections.Generic;
using SiriusConfigurator.DataLayer;
using SiriusConfigurator.StatusHandler;
using SRXml = SiriusConfigurator.BusinessLayer.BEntities.Xml;

namespace SiriusConfigurator
{
    public class ScriptClass
    {   
        string C_FILE_HEADER = @"/*!
* \defgroup (MOD_SERV_BATTERY_MONITORING)
* \{
******************************************************************************
*
* \par Module Owner:
* Huf Group
*
* \par Initial Project:
* 1656.001 BSW
*
******************************************************************************
* \par Description:
* This is configurable source file for the MOD_SERV_BATTERY_MONITORING module.
* It contains the declaration of an array that contains all the ranges defined
* by the user.
*
******************************************************************************
*
* %PCMS_HEADER_SUBSTITUTION_START:%
*
* Configuration Management Information Log (generated by Dimensions CM)
*
*
* CM Item: %PID:%
* Item name: %PM:%
* Location: %ARCHIVE:%
* Revision: %PR:%
* Date: %DATE:%
* Author: %AUTHOR:%
*
* %PCMS_HEADER_SUBSTITUTION_END:% *
******************************************************************************
*
* \par Layer:
* Service
*
* \par Compiler dialect:
* C99
*
* \par Controller:
* Independent
*
* \par Estimated resources:
* | Resource | Amount   | Remarks         |
* | ---------| -------- | ----------------|
* | ROM      | x Byte   | on x controller |
* | RAM      | y Byte   | on x controller |
* | NVRAM    | z Byte   | on x controller |
* | Runtime Init | X ms |                 |
* | Runtime Task | X ms |                 |
*
******************************************************************************/";

        string C_FILE_FOOTER = @"/* %PCMS_HEADER_SUBSTITUTION_START:%
******************************************************************************
* Document Management Information Log (generated by Dimensions CM)
*
* Description:
* %PD:%
*
* Used by Baselines:
* %PIRB:%
*
* Used by Dimensions CM Projects:
* %PIRW:%
*
* Change History:
* %PL:%
*
* %PCMS_HEADER_SUBSTITUTION_END:%
*/";
	
        string H_FILE_HEADER = @" /*!
* \defgroup (MOD_SERV_BATTERY_MONITORING)
* \{
******************************************************************************
*
* \par Module Owner:
* Huf Group
*
* \par Initial Project:
* 1656.001 BSW
*
******************************************************************************
* \par Description:
* This is the configurable header file for the MOD_SERV_BATTERY_MONITORING module.
* Contains definitions for types, defines and external functions' declarations.
*
******************************************************************************
*
* %PCMS_HEADER_SUBSTITUTION_START:%
*
* Configuration Management Information Log (generated by Dimensions CM)
*
*
* CM Item: %PID:%
* Item name: %PM:%
* Location: %ARCHIVE:%
* Revision: %PR:%
* Date: %DATE:%
* Author: %AUTHOR:%
*
* %PCMS_HEADER_SUBSTITUTION_END:% *
******************************************************************************
*
* \par Layer:
* Service
*
* \par Compiler dialect:
* C99
*
* \par Controller:
* Independent
*
* \par Estimated resources:
* | Resource | Amount   | Remarks         |
* | ---------| -------- | ----------------|
* | ROM      | x Byte   | on x controller |
* | RAM      | y Byte   | on x controller |
* | NVRAM    | z Byte   | on x controller |
* | Runtime Init | X ms |                 |
* | Runtime Task | X ms |                 |
*
******************************************************************************/ ";

        string H_FILE_FOOTER = @"/* %PCMS_HEADER_SUBSTITUTION_START:%
******************************************************************************
* Document Management Information Log (generated by Dimensions CM)
*
* Description:
* %PD:%
*
* Used by Baselines:
* %PIRB:%
*
* Used by Dimensions CM Projects:
* %PIRW:%
*
* Change History:
* %PL:%
*
* %PCMS_HEADER_SUBSTITUTION_END:%
*/";

        private StringBuilder CGenerationStream;
		private StringBuilder HGenerationStream;
        private DL_Component siriusApp;
        /* Add here all global variables */	
		bool callbackEnabled; //variable used to determine if there is at least one callback enabled (for a range or for unknown range)
		List<NodeExt> BatMonRange;
		List<NodeExt> BatMonGeneralConfig;
		int noOfRanges;
        public ScriptClass()
        {
            siriusApp = new DL_Component();
			CGenerationStream = new StringBuilder();
            HGenerationStream = new StringBuilder();
            /* add here all global variables initialization */
			BatMonRange = siriusApp.GetNode("BatMonRange");
			BatMonGeneralConfig = siriusApp.GetNode("BatMonGeneralConfig");
			noOfRanges = BatMonRange.Count;			
			if (BatMonGeneralConfig[0].GetAttribute("EnableCallbackUnknown") == "true")
			{
				callbackEnabled = true;
			}
			for (int i = 0; i < noOfRanges; i++)
			{
				//check if callback is enabled
				if (BatMonRange[i].GetAttribute("EnableCallback") == "true")
				{
					callbackEnabled = true;
				}
			}
	    }

		public string Dynamic(NodeExt node, SRXml.AttributesXml attribute)
		{
	    	/* This function is called for every node and attribute each time a module is added in Sirius or the project is loaded. It is checked also when the value of an attribute is changed. */
			/* Using this function attributes can be enabled/disabled/set to an defined value. */ 
			//MessageHandler.SetLog(MessageHandler.ActionTypes.OK, "CheckAttribute reached--"+node.Name+ "  "+attribute.Attribute);
     		//get the number of bits for ADC number type
			string bits_str = BatMonGeneralConfig[0].GetAttribute("ADCBitLength");
			int bits = Int32.Parse(bits_str);
			int nextPower = 0;
			if (bits > 0 && bits <= 8)
			{
				nextPower = 8;
			}
			else 
			
				if (bits > 8 && bits <= 16)
				{
					nextPower = 16;
				}
			
			else
			
				if (bits > 16 && bits <= 32)
				{
					nextPower = 32;
				}

			if (attribute.Attribute == "ADCBitLength")
			{
				SRXml.AttributesXml ADCReadIfReturnType = node.Attributes.Find(x => x.Attribute == "ADCReadIfReturnType");
				siriusApp.SetValueOfAttribute(node, ADCReadIfReturnType, "U"+nextPower);
				siriusApp.SetEnable(node, ADCReadIfReturnType, false);
			}	
			return "OK";
		}
		
		//OK,WARNING,ERROR,FATAL_ERROR
        public string Validate()
		{
			/* This function is called by Sirius to validate the values of attributes defined by user. 
			   An warning or error can be defined into this function in case values are not correct. In case of an error user can not generate the code for the selected module. */
			
            string retVal = "OK";
            uint counter = 0;
			uint low, high, low_next; //used for range threshold values
			uint hysteresis = UInt32.Parse(BatMonGeneralConfig[0].GetAttribute("Hysteresis"));
			string bits_str = BatMonGeneralConfig[0].GetAttribute("ADCBitLength");
			int bits = Int32.Parse(bits_str);
			string RangeChangeCallback = BatMonGeneralConfig[0].GetAttribute("RangeChangeCallback");

			//check if there is a single normal operating range defined
			for (int i = 0; i < noOfRanges; i++)
			{
				if (BatMonRange[i].GetAttribute("NormalOperatingRange") == "true")
				{
					counter++;
				}				
			}
			if (counter != 1)
			{
				retVal = "ERROR";
				MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "Please enable NormalOperatingRange attribute for one range."); 
			}
			
			for (int i = 0; i < noOfRanges; i++)
			{
				low = UInt32.Parse(BatMonRange[i].GetAttribute("ThresholdLow"));
				high = UInt32.Parse(BatMonRange[i].GetAttribute("ThresholdHigh"));
				//check if high threshold is bigger than low threshold
				if (low >= high)
				{
					retVal = "ERROR";
					MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "BatMonRange["+i+"]: ThresholdLow value must be less than ThresholdHigh value.");					
				}
				else
				{	
					//check if the hysteresis is less than the difference between high and low threshold
					if (hysteresis >= (high - low))
					{
						MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "BatMonRange["+i+"]: Hysteresis is bigger than the difference between this range's limits. Please set a larger range or set a smaller hysteresis.");
					}
					
					//check if the ranges are continuous 
					if (i < noOfRanges - 1)
					{
						low_next = UInt32.Parse(BatMonRange[i + 1].GetAttribute("ThresholdLow"));
						if (high != low_next)
						{
							retVal = "ERROR";
							MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "BatMonRange["+i+"]: Ranges must be continuous. ThresholdHigh for BatMonRange["+i+"] must be equal to ThresholdLow for BatMonRange["+(i+1)+"].");							
						}
					}						
				}
					
			}
			
			//check if the threshold values and hysteresis value are smaller than the ADC max value
			//get the number of bits for ADC number type			
			uint maxADCvalue = (uint)(Math.Pow(2, bits) - 1);

			if (hysteresis > maxADCvalue)
			{
				retVal = "ERROR";
				MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "Hysteresis value has to be less than ADC maximum value.");					
			}
			else
			{
				for (int i = 0; i < noOfRanges; i++)
				{
					low = UInt32.Parse(BatMonRange[i].GetAttribute("ThresholdLow"));
					high = UInt32.Parse(BatMonRange[i].GetAttribute("ThresholdHigh"));
					if ((low > maxADCvalue) || (high > maxADCvalue))
					{
						retVal = "ERROR";
						MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "BatMonRange["+i+"]: Threshold high and low values have to be less than ADC maximum value.");					
					}			
				}
			}
			
			if ((callbackEnabled == true) && (RangeChangeCallback.Equals("")))
			{
				retVal = "ERROR";
				MessageHandler.SetLog(MessageHandler.ActionTypes.FATAL_ERROR, "Please set a name to RangeChangeCallback attribute, or disable all callbacks (for all ranges and unknown range).");	
			}

			return retVal;

		}
		
	    private void AddCFileHeader()
        {
            CGenerationStream.Append(C_FILE_HEADER);
            CGenerationStream.AppendLine();
        }
		
   		private void AddCIncludes()
		{
		    CGenerationStream.AppendLine("#include \"BatMon.h\"");
		}
		
		 private void AddCFileFooter()
        {
            CGenerationStream.Append(C_FILE_FOOTER);
            CGenerationStream.AppendLine();
        }
		
		private void CompleteCFile()
        {
            string pathCFile = @"..\GenFiles\Source\BatMon_LCfg.c";
            System.IO.File.WriteAllText(pathCFile, CGenerationStream.ToString());
        }

		private void GenerateCFile()
        {
		
            AddCFileHeader();

            AddCIncludes();

            CGenerationStream.AppendLine();
			
			
			/* Add here the code that shall be generated based on the user configuration from Sirius */  
			CGenerationStream.AppendLine("const BatMon_RangeParamsType BatMon_RangeParams_AS[BATMON_NO_OF_RANGES + BATMON_UNKNOWN_RANGE_ELEMENT] =" );
			CGenerationStream.AppendLine("{");
			for (int i = 0; i < noOfRanges; i++)
			{
				CGenerationStream.AppendLine("\t/*" + BatMonRange[i].GetAttribute("RangeName") + "*/");
				CGenerationStream.AppendLine("\t{");
				CGenerationStream.AppendLine("\t\t"+BatMonRange[i].GetAttribute("EnableCallback").ToUpper()+","+"\t/*Range change callback enable*/");
				CGenerationStream.AppendLine("\t\t"+BatMonRange[i].GetAttribute("ThresholdLow")+"u,"+"\t/*Low threshold*/");
				CGenerationStream.AppendLine("\t\t"+BatMonRange[i].GetAttribute("ThresholdHigh")+"u\t/*High threshold*/");
				CGenerationStream.AppendLine("\t},");
			}
							
			CGenerationStream.AppendLine("\t/* Unknown range */");
			CGenerationStream.AppendLine("\t{");
			CGenerationStream.AppendLine("\t\t"+BatMonGeneralConfig[0].GetAttribute("EnableCallbackUnknown").ToUpper()+","+"\t/*Unknown range callback enable*/");
			CGenerationStream.AppendLine("\t\tBATMON_MAX_VOLTAGE_VALUE,\t/*Low threshold - this is the global high threshold, everything above this threshold is considered UNKNOWN range*/");
			CGenerationStream.AppendLine("\t\tBATMON_MIN_VOLTAGE_VALUE\t/*High threshold - this is the global low threshold, everything below this threshold is considered UNKNOWN range*/");
			CGenerationStream.AppendLine("\t}");
			CGenerationStream.AppendLine("};");

            AddCFileFooter();
			
            CompleteCFile();		
		}
		
		private void AddHFileHeader()
        {
            HGenerationStream.Append(H_FILE_HEADER);
            HGenerationStream.AppendLine();
        }
		
        private void AddHIncludes()
        {
		   HGenerationStream.AppendLine("#include \"Std_Types.h\"");
		}

        private void AddHFileFooter()
        {
            HGenerationStream.Append(H_FILE_FOOTER);
            HGenerationStream.AppendLine();
        }

        private void CompleteHFile()
        {
            string pathHFile = @"..\GenFiles\Source\BatMon_Cfg.h";
           
            System.IO.File.WriteAllText(pathHFile, HGenerationStream.ToString());
        }

		
		private void GenerateHFile()
        {
            AddHFileHeader();

            HGenerationStream.AppendLine("#ifndef BATMON__CFG_H_                   /* To avoid double inclusion */");
            HGenerationStream.AppendLine("#define BATMON__CFG_H_");
            HGenerationStream.AppendLine();         	   
            AddHIncludes(); 
            HGenerationStream.AppendLine();
			/* Add here the code that shall be generated based on the user configuration from Sirius */   						
			string normalRange = ""; //string to hold the user defined name of the normal range
			string RangeChangeCallback = BatMonGeneralConfig[0].GetAttribute("RangeChangeCallback");
			string thresholdHigh = BatMonRange[noOfRanges - 1].GetAttribute("ThresholdHigh");
			string thresholdLow = BatMonRange[0].GetAttribute("ThresholdLow");
			HGenerationStream.AppendLine("/* polyspace +2 MISRA-C3:D4.9 [Not a defect : Unset] \"This macro is used to facilitate an easy adaptation\" */");
			HGenerationStream.Append("#define BATMON_RANGE_CHANGE_CALLBACK(Range)");
			if (callbackEnabled == true)
			{
				HGenerationStream.Append("\t"+ RangeChangeCallback + "(Range)");
			}
			HGenerationStream.AppendLine("\t/*Function called when there is a change in the voltage range*/");
			HGenerationStream.AppendLine("#define BATMON_READ_ADC_IF()\t"+ BatMonGeneralConfig[0].GetAttribute("ADCReadInterface") + "()\t/*Function used to read the value from the ADC*/");
			
			//check if unknown callback option is enabled
			if (BatMonGeneralConfig[0].GetAttribute("EnableCallbackUnknown") == "false")
			{
				HGenerationStream.AppendLine("#define BATMON_UNKNOWN_CALLBACK_ENABLED_CFG\tSTD_OFF\t/*Callback disabled when entering unknown range*/");
			}
			else
			{
				HGenerationStream.AppendLine("#define BATMON_UNKNOWN_CALLBACK_ENABLED_CFG\tSTD_ON\t/*Callback enabled when entering unknown range*/"); 
			}
			HGenerationStream.AppendLine("#define BATMON_NO_OF_RANGES\t((BatMon_RangeStateType)("+ noOfRanges + "u))\t/*Number of ranges defined by user*/");
			HGenerationStream.AppendLine("#define BATMON_HYSTERESIS\t((BatMon_AdcValueType)("+ BatMonGeneralConfig[0].GetAttribute("Hysteresis") + "u))\t/*The value of hysteresis*/");
			HGenerationStream.AppendLine("#define BATMON_MAX_VOLTAGE_VALUE\t((BatMon_AdcValueType)("+ thresholdHigh + "u))\t/*Maximum value of all ranges*/");
			HGenerationStream.AppendLine("/* polyspace +1 MISRA-C3:14.3 [Not a defect:Unset] \"The value of BATMON_MIN_VOLTAGE_VALUE is configurable by the user, so the condition won't always be invariant(only when the value of the define is 0u)\" */");
			HGenerationStream.AppendLine("#define BATMON_MIN_VOLTAGE_VALUE\t((BatMon_AdcValueType)("+ thresholdLow + "u))\t/*Minimum value of all ranges*/");	
			HGenerationStream.AppendLine("#define BATMON_UNKNOWN_RANGE_ELEMENT\t((BatMon_RangeStateType)(1u))\t/*The unknown range element increases the size of the ranges array by 1.*/");
			HGenerationStream.AppendLine("");
			HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:2.5 [Not a defect:Unset] \"The macros can be used when integrating the module\" */");
			HGenerationStream.AppendLine("/*User defined ranges*/");
			for (int i = 0; i < noOfRanges; i++)
			{
				//find the normal operating range
				if (BatMonRange[i].GetAttribute("NormalOperatingRange") == "true")
				{
					normalRange = BatMonRange[i].GetAttribute("RangeName");
				}
				//write ranges defined by the user
				HGenerationStream.AppendLine("#define " + BatMonRange[i].GetAttribute("RangeName") + "\t((BatMon_RangeStateType)(" + i + "u))");
			}
			HGenerationStream.AppendLine("/* polyspace-end MISRA-C3:2.5 [Not a defect:Unset] \"The macros can be used when integrating the module\" */");
			HGenerationStream.AppendLine("#define BATMON_UNKNOWN_RANGE\t((BatMon_RangeStateType)(" + noOfRanges + "u))\t/*The index of the unknown range*/");	
			HGenerationStream.AppendLine("#define BATMON_LAST_USER_DEFINED_RANGE\t((BatMon_RangeStateType)("+ (noOfRanges-1)+"u))\t/*The index of the last user defined range*/");		
			HGenerationStream.AppendLine("#define BATMON_NORMAL_RANGE\t" + normalRange +"\t/*The index of the normal range*/");
			HGenerationStream.AppendLine("");
			HGenerationStream.AppendLine("/*User defined data types*/");

			string adcType = BatMonGeneralConfig[0].GetAttribute("ADCReadIfReturnType");
			HGenerationStream.AppendLine("/*[SWPS_SWS_BatMon_00003]*/");
			HGenerationStream.AppendLine("typedef " + adcType + " BatMon_AdcValueType;\t /*Data type of number returned by ADC interface function.*/");
			//max number of ranges is 255
			HGenerationStream.AppendLine("/*[SWPS_SWS_BatMon_00004]*/");
			HGenerationStream.AppendLine("typedef U8 BatMon_RangeStateType;\t/*Data type for range IDs*/");
			
			//define interface functions
			HGenerationStream.AppendLine("");
			HGenerationStream.AppendLine("/*Interface functions*/");
			if (callbackEnabled == true)
			{
				HGenerationStream.AppendLine("/* polyspace +3 MISRA-C3:8.5 [Not a defect:Unset] \"Was decided that all configured functions be declared as extern into the configuration file\" */");
				HGenerationStream.AppendLine("extern BatMon_AdcValueType " + BatMonGeneralConfig[0].GetAttribute("ADCReadInterface") +"(void);");	
				HGenerationStream.AppendLine("extern void " + RangeChangeCallback + "(BatMon_RangeStateType BatMon_NewRange);");
			}
			else
			{
				HGenerationStream.AppendLine("/* polyspace +1 MISRA-C3:8.5 [Not a defect:Unset] \"Was decided that all configured functions be declared as extern into the configuration file\" */");
				HGenerationStream.AppendLine("extern BatMon_AdcValueType " + BatMonGeneralConfig[0].GetAttribute("ADCReadInterface") +"(void);");	
			}

            HGenerationStream.AppendLine("#endif /* BATMON__CFG_H_ */");

            HGenerationStream.AppendLine();

            AddHFileFooter();

            CompleteHFile();
        }

		public string Generate()
        { 
		    /* This function is called by Sirius when Generate option is selected and will generate the configuration files. It is available just when validation occurred without errors. */
            GenerateHFile();
			GenerateCFile();
            return "OK";
        }
	}
}
