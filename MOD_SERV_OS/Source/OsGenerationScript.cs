using System.Text;
using System.Collections.Generic;
using SiriusConfigurator.DataLayer;
using SiriusConfigurator.StatusHandler;
using SRXml = SiriusConfigurator.BusinessLayer.BEntities.Xml;

namespace SiriusConfigurator
{
    public class ScriptClass
    {    
        string C_FILE_HEADER = @"/*!
 * \defgroup MOD_SERV_OS (Os_LCfg.c)
 * \{
 ******************************************************************************
 * \image html ""Kopf_oZusatz_A4hoch_4C.jpg""
 *
 * \par Module Owner:
 * Huf Group
 *
 * \par Initial Project:
 * 1656.001 BSW
 *
 ******************************************************************************
 * \par Description:
 * Generated configuration source file for Serv OS.
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
 * Operating System, Service Layer
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
        string H_FILE_HEADER = @"/*!
 * \defgroup MOD_SERV_OS (Os_Cfg.h)
 * \{
 ******************************************************************************
 * \image html ""Kopf_oZusatz_A4hoch_4C.jpg""
 *
 * \par Module Owner:
 * Huf Group
 *
 * \par Initial Project:
 * 1656.001 BSW
 *
 ******************************************************************************
 * \par Description:
 * Generated configuration header file for Serv OS.
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
 * Operating System, Service Layer
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



string HCommon_FILE_HEADER = @"/*!
 * \defgroup MOD_SERV_OS (Os_CommonCfg.h)
 * \{
 ******************************************************************************
 * \image html ""Kopf_oZusatz_A4hoch_4C.jpg""
 *
 * \par Module Owner:
 * Huf Group
 *
 * \par Initial Project:
 * 1656.001 BSW
 *
 ******************************************************************************
 * \par Description:
 * Generated common configuration header file for Serv OS and Mcal OS.
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
 * Operating System, Service Layer
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
		private StringBuilder HCommonGenerationStream;
        private DL_Component siriusApp;
        private List<NodeExt> taskList;
		private List<NodeExt> OsAlarmList;
        private NodeExt osGeneral;
        private List<NodeExt> osTickNode; 
        private List<int> priorityList;
        private List<int> sortedPrioList;
        private int noOfDistinctPrios = 0;

        public ScriptClass()
        {
            siriusApp = new DL_Component();
            CGenerationStream = new StringBuilder();
            HGenerationStream = new StringBuilder();
			HCommonGenerationStream = new StringBuilder();
            taskList = siriusApp.GetNode("OsCyclicTask");
			OsAlarmList = siriusApp.GetNode("OsAlarm");
            osGeneral = siriusApp.GetNode("OsServGeneral")[0];
            osTickNode = siriusApp.GetNode("OsTick");
            sortedPrioList = new List<int>();
            priorityList = new List<int>();
        }

		public string Dynamic(NodeExt node, SRXml.AttributesXml attribute)
		{
			
			//MessageHandler.SetLog(MessageHandler.ActionTypes.OK, "CheckAttribute reached--"+node.Name+ "  "+attribute.Attribute);
            						
			if ((node.Name == "OsServGeneral") && (attribute.Attribute == "OsBackgroundTask") && (attribute.Value == "false"))
			{
				SRXml.AttributesXml TaskName = node.Attributes.Find(x => x.Attribute == "OsBackgroundTaskName");
				siriusApp.SetEnable(node, TaskName, false);
			}
			
			if ((node.Name == "OsServGeneral") && (attribute.Attribute == "OsBackgroundTask") && (attribute.Value == "true"))
			{
				SRXml.AttributesXml TaskName = node.Attributes.Find(x => x.Attribute == "OsBackgroundTaskName");
				siriusApp.SetEnable(node, TaskName, true);
			}
			
			return "OK";
		}
		
		//OK,WARNING,ERROR,FATAL_ERROR
        public string Validate()
		{
            string retVal = "OK";
            bool status;
            int tickUs = 0;
            int index;

     		if (osGeneral.GetAttribute("OsBackgroundTask") == "true")
            {
				string BackgroundTsk;
				BackgroundTsk = osGeneral.GetAttribute("OsBackgroundTaskName").Trim();
				if(BackgroundTsk.Equals(""))
				{
				    MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "OsBackgroundTaskName must not be empty when OsBackgroundTask is set true");
                    retVal = "ERROR";
                    return retVal;	
				}
                else
				{
					status = ValidateIdentifier(BackgroundTsk);

                    if (false == status)
                    {
                        MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "OsBackgroundTaskName is not a valid identifier");
                        retVal = "ERROR";
                        return retVal;
                    }
				}
            }
			
			if (osTickNode.Count > 0)
			{
				status = int.TryParse(osTickNode[0].GetAttribute("OsTickTimeUs"), out tickUs);
			    for ( index = 0; index < taskList.Count; index++)
                {
                    float cycleTimeMs, offset;

                    float.TryParse(taskList[index].GetAttribute("OsTaskCycleTimeMs"), out cycleTimeMs);
                    if ((cycleTimeMs * 1000) % tickUs != 0)
                    {
                        MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "OsTaskCycleTimeMs has to be a multiple of OsTickTimeUs");
                        retVal = "ERROR";
                        return retVal;
                    }

                    float.TryParse(taskList[index].GetAttribute("OsTaskOffsetMs"), out offset);
                    if ((offset * 1000) % tickUs != 0)
                    {
                        MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "OsTaskOffsetMs has to be a multiple of OsTickTimeUs");
                        retVal = "ERROR";
                        return retVal;
                    }
				}
			}
			else
			{
				MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "OsMcal module shall be added in Sirius");
                retVal = "ERROR";
                return retVal;
			}
			         
            string confClass = osGeneral.GetAttribute("OsConformanceClass");

            if (confClass == "BCC1") /* only basic tasks, limited to one activation request per task and one task per priority, while all tasks have different priorities */
            {
                List<int> prioList = new List<int>();
                for (index = 0; index < taskList.Count; index++)
                {
                    if (taskList[index].GetAttribute("OsTaskActivation") != "1")
                    {
                        MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "Os task "+ taskList[index].GetAttribute("OsTaskName")+ " maximum allowed activations is exceeded ( maximum 1 for BCC1 ). See OsConformanceClass");
                        retVal = "ERROR";
                        return retVal;
                    }

                    int prio;
                    int.TryParse(taskList[index].GetAttribute("OsTaskPriority"), out prio);

                    if (prioList.Exists(x => x == prio))
                    { /* priority already exists */
                        MessageHandler.SetLog(MessageHandler.ActionTypes.ERROR, "Multiple tasks with priority " + taskList[index].GetAttribute("OsTaskPriority") + " defined. See OsConformanceClass");
                        retVal = "ERROR";
                        return retVal;
                    }
                    else
                    {
                        prioList.Add(prio);
                    }
                }
            }

            return retVal;
		}
		
		private bool ValidateIdentifier(string identifier)
        {
            bool valid = true;

            if (char.IsLetter(identifier[0]))
            {
                char c;

                for (int i = 1; i < identifier.Length; i++)
                {
                    c = identifier[i];
                    if ((!char.IsLetterOrDigit(c)) && (c != '_'))
                    {
                        valid = false;
                        break;
                    }
                }
            }
            else
            {
                //first character is not a letter
                valid = false;
            }

            return valid;
        }
		
        private void AddCFileHeader()
        {
			CGenerationStream.Append("/* polyspace MISRA-C3:1.1 [Justified:Low]\"The defined macros are controller specific macros from registers header file\" */");
			CGenerationStream.AppendLine();
            CGenerationStream.Append(C_FILE_HEADER);
            CGenerationStream.AppendLine();
        }

		 private void AddCIncludes()
        {
            CGenerationStream.AppendLine(@"/* Include files */");
            CGenerationStream.AppendLine("#include \"Os.h\"");
        }
		
        private void AddCFileFooter()
        {
            CGenerationStream.Append(C_FILE_FOOTER);
            CGenerationStream.AppendLine();
        }

        private void CompleteCFile()
        {
            string pathCFile = @"..\GenFiles\Source\Os_LCfg.c";
            System.IO.File.WriteAllText(pathCFile, CGenerationStream.ToString());
        }

        private void AddHFileHeader()
        {
            HGenerationStream.Append(H_FILE_HEADER);
            HGenerationStream.AppendLine();
        }

        private void AddHIncludes()
        {
			HGenerationStream.AppendLine("#include \"Os_CommonCfg.h\"");
			HGenerationStream.AppendLine("#include \"Os_Mcal.h\"");
			if (osGeneral.GetAttribute("OsServIncludeHeaderFile").Trim() != "")
			{
				 HGenerationStream.AppendLine("/*[SWPS_SWS_SERVOS_00108]*/");
			    HGenerationStream.AppendLine("#include \"" + osGeneral.GetAttribute("OsServIncludeHeaderFile") + "\"");
			}
        }

        private void AddHFileFooter()
        {
            HGenerationStream.Append(H_FILE_FOOTER);
            HGenerationStream.AppendLine();
        }

        private void CompleteHFile()
        {
            string pathHFile = @"..\GenFiles\Source\Os_Cfg.h";
            System.IO.File.WriteAllText(pathHFile, HGenerationStream.ToString());
        }
		
		
		private void AddHCommonFileHeader()
        {
            HCommonGenerationStream.Append(HCommon_FILE_HEADER);
            HCommonGenerationStream.AppendLine();
        }
		

        private void AddHCommonIncludes()
        {
			
        }

        private void AddHCommonFileFooter()
        {
            HCommonGenerationStream.Append(H_FILE_FOOTER);
            HCommonGenerationStream.AppendLine();
        }

        private void CompleteHCommonFile()
        {
            string pathHCommonFile = @"..\GenFiles\Source\Os_CommonCfg.h";
            System.IO.File.WriteAllText(pathHCommonFile, HCommonGenerationStream.ToString());
        }

        private void PrintSortedTaskPrios()
        {
            int prevEl;
            int i;
            priorityList.Sort(); //sorts ascending

            /* print in descending order (highest priority first), remove duplicates */
            /* Add first element */
            i = (priorityList.Count - 1);
            CGenerationStream.Append(priorityList[i].ToString() + "u");
            sortedPrioList.Add(priorityList[i]);
            noOfDistinctPrios++;
            prevEl = priorityList[i];

            for (i = (priorityList.Count-2); i >= 0; i--)
            {
                //element is distinct from the previous element
                if (priorityList[i] < prevEl)
                {
                    CGenerationStream.Append(", " + priorityList[i].ToString() + "u");
                    sortedPrioList.Add(priorityList[i]);
                    noOfDistinctPrios++;
                    prevEl = priorityList[i];
                }      
            }
        }

        private void GenerateCFile()
        {
            /* Generate Os_GenCfg.c */
            /*******************************/

            int index;

            AddCFileHeader();

            AddCIncludes();
            CGenerationStream.AppendLine();

            for (index = 0; index < taskList.Count; index++)
            {
                int priority;
                int.TryParse(taskList[index].GetAttribute("OsTaskPriority"), out priority);
                priorityList.Add(priority);
            }
			
			CGenerationStream.AppendLine("/* [SWPS_SWS_SERVOS_00115], [SWPS_SWS_SERVOS_00116], [SWPS_SWS_SERVOS_00117],[SWPS_SWS_SERVOS_00118], [SWPS_SWS_SERVOS_00119], [SWPS_SWS_SERVOS_00120], [SWPS_SWS_SERVOS_00121], [SWPS_SWS_SERVOS_00122], [SWPS_SWS_SERVOS_00123], [SWPS_SWS_SERVOS_00124] */ ");

            CGenerationStream.Append("const U8 Os_SortedPriorityList[OS_NO_OF_PRIORITIES] = {");
            PrintSortedTaskPrios();
            CGenerationStream.AppendLine("};\n");

            /* Define Os_TaskCfgData */

            CGenerationStream.AppendLine("const Os_TaskCfgDataType Os_TaskCfgData[OS_NO_OF_CYCLIC_TASKS] = {");
            CGenerationStream.AppendLine("/* functionPointer priority prioIndex scheduling noAllowedActivations alarmID */");

			for (index = 0; index < taskList.Count; index++)
            {
                CGenerationStream.Append("\t" + "{   &" + taskList[index].GetAttribute("OsTaskName") + "func, "); 
              
                CGenerationStream.Append(taskList[index].GetAttribute("OsTaskPriority") + "u, ");
                int priority;
                int.TryParse(taskList[index].GetAttribute("OsTaskPriority"), out priority);
                int prioIndex = sortedPrioList.IndexOf(priority);
                CGenerationStream.Append(prioIndex.ToString() + "u, ");

                CGenerationStream.Append(taskList[index].GetAttribute("OsTaskSchedule") + "_PREEMPTIVE, ");
               
                CGenerationStream.Append(taskList[index].GetAttribute("OsTaskActivation")+ "u, ");
                CGenerationStream.Append(index.ToString() + "u}");

                if (index < (taskList.Count - 1))
                {
                    CGenerationStream.Append(",");
                }
                CGenerationStream.AppendLine(" /*" + taskList[index].GetAttribute("OsTaskName") + "*/");
            }
            CGenerationStream.AppendLine("};");
            CGenerationStream.AppendLine();

            CGenerationStream.AppendLine("const Os_CyclicAlarmCfgDataType Os_CyclicAlarmCfgData[NUMBER_OF_CYCLIC_ALARMS] = {");
            CGenerationStream.AppendLine("/* counterRef cycleTime initialCycleTime taskID */");

            int tickUs;
            float ticksPerMs;
            int.TryParse(osTickNode[0].GetAttribute("OsTickTimeUs"), out tickUs);
            ticksPerMs = (float)1000.0 / tickUs;// can be <1 if tickUs > 1000us

            for (index = 0; index < taskList.Count; index++)
            {
                CGenerationStream.Append("\t" + "{   &Os_TickCounter, ");

                int  cycleTimeTicks;
                float cycleTimeMs, offset;
                
                float.TryParse(taskList[index].GetAttribute("OsTaskCycleTimeMs"), out cycleTimeMs);                           
                cycleTimeTicks = (int) (cycleTimeMs * ticksPerMs);
                CGenerationStream.Append(cycleTimeTicks.ToString() + "u, "); /* cycleTime in ticks*/

                float.TryParse(taskList[index].GetAttribute("OsTaskOffsetMs"), out offset);
                offset = (int)(offset * ticksPerMs); 
                CGenerationStream.Append(offset.ToString() + "u, "); /* initialCycleTime in ticks*/

                CGenerationStream.Append(index.ToString() + "u}"); /* taskID */
                if (index < (taskList.Count - 1))
                {
                    CGenerationStream.Append(",\n");
                }
            }

            CGenerationStream.AppendLine("\n};");
            CGenerationStream.AppendLine();
			
			/*check if there is at least one single alarm configured*/
			if(OsAlarmList.Count > 0)
			{
				/*generate the structure for single alarms*/
				CGenerationStream.AppendLine("const Os_SingleAlarmCfgDataType Os_SingleAlarmCfgData[NUMBER_OF_SINGLE_ALARMS_CFG] = {");
				CGenerationStream.AppendLine("	/* Callback routine 	counterRef */");
				for(int alarmIndex = 0; alarmIndex < OsAlarmList.Count; alarmIndex++)
				{
					/*generate the pointer to the callback function configured by the user*/
					if(OsAlarmList[alarmIndex].GetAttribute("OsAlarmCallback") == "NULL")
					{
						CGenerationStream.Append("\t" + "{   " + OsAlarmList[alarmIndex].GetAttribute("OsAlarmCallback") + "," );
					}
					else
					{
						CGenerationStream.Append("\t" + "{   &" + OsAlarmList[alarmIndex].GetAttribute("OsAlarmCallback") + ",");
					}
					/*generate the reference to the counter used by the alarm*/
					
					/*check if this is the last element of the structure in order to remove the comma and generate the reference to the counter used by the alarm*/
					if(alarmIndex == (OsAlarmList.Count - 1))
					{
						CGenerationStream.Append("\t" + "&Os_TickCounter}\n");
					}
					else
					{
						CGenerationStream.Append("\t" + "&Os_TickCounter}, \n");
					}
				}
				CGenerationStream.AppendLine("\n};");
				CGenerationStream.AppendLine();

			}

            AddCFileFooter();
            CompleteCFile();
        }

        private void GenerateHFile()
        {
            int index;
            string attributeVal ="";
                  			
            /* Generate Os_Cfg.h */
            /*******************************/
			 AddHFileHeader();

            HGenerationStream.AppendLine("#ifndef OS_GENCFG_H_                   /* To avoid double inclusion */");
            HGenerationStream.AppendLine("#define OS_GENCFG_H_");
            HGenerationStream.AppendLine();
           
            AddHIncludes();
			HGenerationStream.AppendLine("");
            attributeVal = osGeneral.GetAttribute("OsBackgroundTask");
			HGenerationStream.AppendLine("/*[SWPS_SWS_SERVOS_00002], [SWPS_SWS_SERVOS_00003], [SWPS_SWS_SERVOS_00004], [SWPS_SWS_SERVOS_00005], [SWPS_SWS_SERVOS_00006], [SWPS_SWS_SERVOS_00007], [SWPS_SWS_SERVOS_00014], [SWPS_SWS_SERVOS_00015], [SWPS_SWS_SERVOS_00016], [SWPS_SWS_SERVOS_00017], [SWPS_SWS_SERVOS_00018], [SWPS_SWS_SERVOS_00022] */");
           
			/*check if there is at least one single alarm configured*/
			if(((OsAlarmList.Count > 0) && (attributeVal == "true")) || (OsAlarmList.Count > 0))
			{
				HGenerationStream.AppendLine("/*polyspace-begin MISRA-C3:D4.9 [Not a defect:Unset] \"Macros used to facilitate an easier adaptation\" */");
			}
			else
				if(attributeVal == "true")
				{
					HGenerationStream.AppendLine("/* polyspace +5 MISRA-C3:D4.9 [Not a defect:Unset] \"Macros used to facilitate an easier adaptation\" */");
				}

			if(OsAlarmList.Count > 0)
			{
				HGenerationStream.AppendLine("/*Macro for callback routines definitions; this macro has to be used in each single alarm callback routine function*/");
				HGenerationStream.AppendLine("#define ALARMCALLBACK(AlarmCallbackRoutineName) void (AlarmCallbackRoutineName)(void)   /*For future development: Alarm-callback routines run with category 2 interrupts disabled. In the actual implementation, there is no separation between interrupts category.*/");
				HGenerationStream.AppendLine("/*Macro used to convert time from milliseconds to ticks. This macro must only be used for constants times*/");
				HGenerationStream.AppendLine("/*polyspace +1 MISRA-C3:17.7 [Not a defect:Unset] \"It is not a non-void function, it's a function like macro; it can be called as a parameter for other functions.\" */");
				HGenerationStream.AppendLine("#define OS_MS_TO_TICKS(timeInMs)  ((Os_CounterType)((((U32)(timeInMs)) * 1000U) / (((U32)OS_TICK_TIME_US))))");
			}

			HGenerationStream.AppendLine("/* polyspace +3 MISRA-C3:2.5 [Not a defect:Unset] \"The macro is used during integration phase\" */");
			HGenerationStream.AppendLine("/*Macro used to convert time from ticks to milliseconds. This macro must only be used for constants times*/");
			HGenerationStream.AppendLine("#define OS_TICKS2MS_SystemTimer(tick) (((U32)((U32)(tick) * (U32)OS_TICK_TIME_US))/ 1000U)");
            if (attributeVal == "true")
            {
				HGenerationStream.AppendLine("#define OS_BACKGROUND_TASK_FUNC() " + osGeneral.GetAttribute("OsBackgroundTaskName") + "()        /*[SWPS_SWS_SERVOS_00114]*/");
            }
			if(((OsAlarmList.Count > 0) && (attributeVal == "true")) || (OsAlarmList.Count > 0))
			{
				HGenerationStream.AppendLine("/* polyspace-end MISRA-C3:D4.9 [Not a defect:Unset] \"Macros used to facilitate an easier adaptation\"*/");
			}
			HGenerationStream.AppendLine();
            HGenerationStream.AppendLine(@"/* Conformance class: 
* BCC1(only basic tasks, limited to one activation request per task and one task per priority, while all tasks have different priorities)
* BCC2(like BCC1, plus more than one task per priority possible and multiple requesting of task activation allowed) */");
            HGenerationStream.AppendLine("#define OS_CONF_CLASS " + osGeneral.GetAttribute("OsConformanceClass") + "         /*[SWPS_SWS_SERVOS_00111]*/");
            HGenerationStream.AppendLine();

            HGenerationStream.AppendLine("/*Enable non-cyclic tasks*/");

            // attributeVal = osGeneral.GetAttribute("OsNonCyclicTasks"); -------> this feature is not yet available, set value to "false"
            attributeVal = "false";
			 HGenerationStream.AppendLine("/*[SWPS_SWS_SERVOS_00007], [SWPS_SWS_SERVOS_00019], [SWPS_SWS_SERVOS_00020] */");
            if (attributeVal == "false")
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_NON_CYCLIC_TASKS STD_OFF");

            }
            else
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_NON_CYCLIC_TASKS STD_ON");
            }

			HGenerationStream.AppendLine("");
            HGenerationStream.AppendLine("/*Enable not nestable API for enable/disable interrupts - [SWPS_SWS_SERVOS_00110] */");
            attributeVal = osGeneral.GetAttribute("OsEnableDisableAllInterruptsAPIs");
            if(attributeVal == "false")
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_NOT_NESTABLE_INT_API STD_OFF");

            }
            else
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_NOT_NESTABLE_INT_API STD_ON");
            }

            HGenerationStream.AppendLine("/*Enable pre/post task hooks [SWPS_SWS_SERVOS_00105]*/");
            attributeVal = osGeneral.GetAttribute("OsTaskHooks");
            if (attributeVal == "false")
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_TASK_HOOKS STD_OFF");
            }
            else
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_TASK_HOOKS STD_ON");
            }

            HGenerationStream.AppendLine("/*Enable startup hook - [SWPS_SWS_SERVOS_00107]*/");
            attributeVal = osGeneral.GetAttribute("OsStartupHook");
            if (attributeVal == "false")
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_STARTUP_HOOK STD_OFF");

            }
            else
            {
                HGenerationStream.AppendLine("#define OS_ENABLE_STARTUP_HOOK STD_ON");
            }

            HGenerationStream.AppendLine("/* Enable/Disable  GetElapsedValue API - [SWPS_SWS_SERVOS_00112] */");
            if (osGeneral.GetAttribute("GetElapsedValueEn") == "false")
            {
                HGenerationStream.AppendLine("#define OS_GET_ELAPSED_VAL_API STD_OFF");
            }
            else
            {
                HGenerationStream.AppendLine("#define OS_GET_ELAPSED_VAL_API STD_ON");
            }
			
			HGenerationStream.AppendLine("/* Enable/Disable  GetCounterValue API - [SWPS_SWS_SERVOS_00113] */");
            if (osGeneral.GetAttribute("GetCounterValueEn") == "false")
            {
                HGenerationStream.AppendLine("#define OS_GET_COUNTER_VAL_API STD_OFF");
            }
            else
            {
                HGenerationStream.AppendLine("#define OS_GET_COUNTER_VAL_API STD_ON");
            }
            HGenerationStream.AppendLine();
			HGenerationStream.AppendLine("/*Enable/disable single alarms [SWPS_SWS_SERVOS_00125]*/");
			/*check if there is at least one single alarm configured*/
			if(OsAlarmList.Count > 0)
			{
				HGenerationStream.AppendLine("#define OS_SINGLE_ALARMS_ENABLED_CFG STD_ON");
				HGenerationStream.AppendLine();
				HGenerationStream.Append("#define NUMBER_OF_SINGLE_ALARMS_CFG ");
				HGenerationStream.AppendLine(OsAlarmList.Count.ToString() + "u");
				HGenerationStream.AppendLine("/*Single alarms' IDs*/");
				for(int alarmIndex = 0; alarmIndex < OsAlarmList.Count; alarmIndex++)
				{
					/*generate ID macros for each alarm configured*/
					HGenerationStream.AppendLine("#define " + OsAlarmList[alarmIndex].GetAttribute("OsAlarmID") + "\t\t" + alarmIndex + "u");
				}


			}
			else
			{
				HGenerationStream.AppendLine("#define OS_SINGLE_ALARMS_ENABLED_CFG STD_OFF");
			}
			
			HGenerationStream.AppendLine();
            HGenerationStream.Append("#define OS_NO_OF_CYCLIC_TASKS ");
            HGenerationStream.AppendLine(taskList.Count.ToString() + "u");
			
			/*Define counters' IDs*/
			HGenerationStream.AppendLine();
			HGenerationStream.AppendLine("/* polyspace +2 MISRA-C3:2.5 [Not a defect:Unset] \"The macro is used during integration phase\" */");
			HGenerationStream.AppendLine("/*Define counters' IDs*/");
			HGenerationStream.AppendLine("#define SystemTimer      0x00u");
			HGenerationStream.AppendLine();
			
            /* Define task IDs */
			HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:2.5 [Not a defect:Unset] \"Task IDs are used into integration\" */");
            for (index = 0; index < taskList.Count; index++)
            {
                HGenerationStream.AppendLine("#define OS_TASK_ID_" + taskList[index].GetAttribute("OsTaskName") + " " + index.ToString() + "u");
            }
			HGenerationStream.AppendLine("/* polyspace-end MISRA-C3:2.5 [Not a defect:Unset] \"Task IDs are used into integration\" */");
            HGenerationStream.AppendLine("#define OS_TASK_ID_Idle 0xFFu");
            // TODO: check that number of tasks is < 0xFF
            HGenerationStream.AppendLine();

            HGenerationStream.Append("#define NUMBER_OF_CYCLIC_ALARMS ");
            HGenerationStream.AppendLine(taskList.Count.ToString() + "u");
            HGenerationStream.AppendLine();
			

            HGenerationStream.AppendLine("/* Number of distinct task priorities */");
            HGenerationStream.AppendLine("#define OS_NO_OF_PRIORITIES "+ noOfDistinctPrios.ToString() +"u");
            HGenerationStream.AppendLine();

			HGenerationStream.AppendLine("/* Enable/Disable Get/ReleaseResource APIs - [SWPS_SWS_SERVOS_00106]*/");
            if (osGeneral.GetAttribute("OSGetReleaseResourceAPIs") == "false")
            {
                HGenerationStream.AppendLine("#define OS_GET_RELEASE_RESOURCE_API STD_OFF");
            }
            else
            {
                HGenerationStream.AppendLine("#define OS_GET_RELEASE_RESOURCE_API STD_ON");
				HGenerationStream.AppendLine("#define RES_SCHEDULER 0u");
				//HGenerationStream.AppendLine("/* Number of resources */");
				//HGenerationStream.AppendLine("#define OS_NO_OF_RESOURCES 1u");
            }			

            HGenerationStream.AppendLine();
			
            HGenerationStream.AppendLine("/* List of priorities sorted: index 0 contains the highest priority value, index <OS_NO_OF_PRIORITIES - 1> contains");
            HGenerationStream.AppendLine(" * the lowest priority value */");
            HGenerationStream.AppendLine("extern const U8 Os_SortedPriorityList[OS_NO_OF_PRIORITIES];");
            string confClass = osGeneral.GetAttribute("OsConformanceClass");

            if (false == (osGeneral.GetAttribute("OsConformanceClass").Equals("BCC1")))
            {
				HGenerationStream.AppendLine("#define OS_PRIO_QUEUE_SIZE 20u");
                HGenerationStream.AppendLine(@"typedef struct
{
    TaskType taskID[OS_PRIO_QUEUE_SIZE];
    U8 head;
    U8 tail;
    U8 count;
}
Os_TaskPrioQueueType;");
            }

            HGenerationStream.AppendLine();
            HGenerationStream.AppendLine("/* Task configuration */");
            
            HGenerationStream.AppendLine("extern const Os_TaskCfgDataType Os_TaskCfgData[OS_NO_OF_CYCLIC_TASKS];");
            HGenerationStream.AppendLine();

            HGenerationStream.AppendLine("extern const Os_CyclicAlarmCfgDataType Os_CyclicAlarmCfgData[NUMBER_OF_CYCLIC_ALARMS];");
            HGenerationStream.AppendLine();
            /*check if there is at least one single alarm configured*/
			if(OsAlarmList.Count > 0)
			{
				HGenerationStream.AppendLine("extern const Os_SingleAlarmCfgDataType Os_SingleAlarmCfgData[NUMBER_OF_SINGLE_ALARMS_CFG];");
				HGenerationStream.AppendLine();
			}
			
			HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:8.5 [Not a defect:Unset] \"Was decided that all configured functions be declared as extern into the configuration file\" */");
			HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:5.1 [Not a defect:Unset] \"C99 standard is used to compile, Huf naming convention\" */");
            /* Add extern declarations for tasks */
            for (index = 0; index < taskList.Count; index++)
            {
                HGenerationStream.AppendLine("extern TASK(" + taskList[index].GetAttribute("OsTaskName") + ");");
            }
			

            if (osGeneral.GetAttribute("OsBackgroundTask") == "true")
            {
			    HGenerationStream.AppendLine("extern void " + osGeneral.GetAttribute("OsBackgroundTaskName") + "(void);");
            }
			HGenerationStream.AppendLine();
			/*check if there is at least a single alarm configured*/
			if(OsAlarmList.Count > 0)
			{	/*add extern declaration for callback functions*/
				HGenerationStream.AppendLine(/*Extern declaration for single alarm callback functions*/);
				for(int alarmIndex = 0; alarmIndex < OsAlarmList.Count; alarmIndex++)
				{
					if(OsAlarmList[alarmIndex].GetAttribute("OsAlarmCallback") != "NULL")
					{
						HGenerationStream.AppendLine("extern ALARMCALLBACK(" + OsAlarmList[alarmIndex].GetAttribute("OsAlarmCallback") + ");");
					}
				}
			}
			HGenerationStream.AppendLine("/* polyspace-end MISRA-C3:8.5 [Not a defect:Unset] \"Was decided that all configured functions be declared as extern into the configuration file\" */");
            HGenerationStream.AppendLine("/* polyspace-begin MISRA-C3:5.1 [Not a defect:Unset] \"C99 standard is used to compile, Huf naming convention\" */");
			HGenerationStream.AppendLine();

            HGenerationStream.AppendLine("#endif /* OS_GENCFG_H_ */");

            HGenerationStream.AppendLine();

            AddHFileFooter();

            CompleteHFile();
        }

		
		private void GenerateHCommonFile()
		{
			string attributeVal ="";
			
			 /* Generate Os_CommonCfg.h */
            /*******************************/

            AddHCommonFileHeader();

            HCommonGenerationStream.AppendLine("#ifndef OS_COMMONCFG_H_                   /* To avoid double inclusion */");
            HCommonGenerationStream.AppendLine("#define OS_COMMONCFG_H_");
            HCommonGenerationStream.AppendLine();
           
            AddHCommonIncludes();
			
			HCommonGenerationStream.AppendLine("/*Enable background task - [SWPS_SWS_SERVOS_00109] */");
            attributeVal = osGeneral.GetAttribute("OsBackgroundTask");
            if (attributeVal == "false")
            {
                HCommonGenerationStream.AppendLine("#define OS_ENABLE_BACKGROUND_TASK STD_OFF");
            }
            else
            {
                HCommonGenerationStream.AppendLine("#define OS_ENABLE_BACKGROUND_TASK STD_ON");
	        }
			
			HCommonGenerationStream.AppendLine();
			HCommonGenerationStream.AppendLine("#endif /* OS_COMMONCFG_H_ */");

            HCommonGenerationStream.AppendLine();

            AddHCommonFileFooter();

            CompleteHCommonFile();
		}
        public string Generate()
        { 
            GenerateCFile();
            GenerateHFile();
			GenerateHCommonFile();
            return "OK";
        }
	}
}
