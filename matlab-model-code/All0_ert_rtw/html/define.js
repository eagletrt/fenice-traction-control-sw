function CodeDefine() { 
this.def = new Array();
this.def["ert_main.c:rtM_"] = {file: "ert_main_c.html",line:27,type:"var"};
this.def["ert_main.c:rtMPtr"] = {file: "ert_main_c.html",line:28,type:"var"};
this.def["ert_main.c:rtDW"] = {file: "ert_main_c.html",line:29,type:"var"};
this.def["ert_main.c:rtU_Driver_req"] = {file: "ert_main_c.html",line:32,type:"var"};
this.def["ert_main.c:rtU_u_bar"] = {file: "ert_main_c.html",line:35,type:"var"};
this.def["ert_main.c:rtU_omega_rr"] = {file: "ert_main_c.html",line:38,type:"var"};
this.def["ert_main.c:rtU_omega_rl"] = {file: "ert_main_c.html",line:41,type:"var"};
this.def["ert_main.c:rtU_yaw_rate"] = {file: "ert_main_c.html",line:44,type:"var"};
this.def["ert_main.c:rtU_Steeringangle"] = {file: "ert_main_c.html",line:47,type:"var"};
this.def["ert_main.c:rtU_Brake"] = {file: "ert_main_c.html",line:50,type:"var"};
this.def["ert_main.c:rtY_Tm_rr"] = {file: "ert_main_c.html",line:53,type:"var"};
this.def["ert_main.c:rtY_Tm_rl"] = {file: "ert_main_c.html",line:56,type:"var"};
this.def["rt_OneStep"] = {file: "ert_main_c.html",line:70,type:"fcn"};
this.def["main"] = {file: "ert_main_c.html",line:108,type:"fcn"};
this.def["lambda_ref"] = {file: "All0_c.html",line:25,type:"var"};
this.def["All0.c:look1_binlxpw"] = {file: "All0_c.html",line:38,type:"fcn"};
this.def["All0.c:look1_pbinlcapw"] = {file: "All0_c.html",line:95,type:"fcn"};
this.def["All0.c:Slip_est1"] = {file: "All0_c.html",line:170,type:"fcn"};
this.def["All0.c:IfActionSubsystem"] = {file: "All0_c.html",line:188,type:"fcn"};
this.def["All0.c:IfActionSubsystem1"] = {file: "All0_c.html",line:201,type:"fcn"};
this.def["All0_step"] = {file: "All0_c.html",line:210,type:"fcn"};
this.def["All0_initialize"] = {file: "All0_c.html",line:628,type:"fcn"};
this.def["RT_MODEL"] = {file: "All0_h.html",line:45,type:"type"};
this.def["DW"] = {file: "All0_h.html",line:58,type:"type"};
this.def["ConstP"] = {file: "All0_h.html",line:111,type:"type"};
this.def["rtConstP"] = {file: "All0_data_c.html",line:25,type:"var"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:59,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:60,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:73,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:74,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:92,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["ert_main_c.html"] = "../ert_main.c";
	this.html2Root["ert_main_c.html"] = "ert_main_c.html";
	this.html2SrcPath["All0_c.html"] = "../All0.c";
	this.html2Root["All0_c.html"] = "All0_c.html";
	this.html2SrcPath["All0_h.html"] = "../All0.h";
	this.html2Root["All0_h.html"] = "All0_h.html";
	this.html2SrcPath["All0_data_c.html"] = "../All0_data.c";
	this.html2Root["All0_data_c.html"] = "All0_data_c.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"ert_main_c.html","All0_c.html","All0_h.html","All0_data_c.html","rtwtypes_h.html"];
