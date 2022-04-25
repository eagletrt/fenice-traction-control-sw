function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.var["lambda_ref"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	size: 8};
	 this.metricsArray.fcn["Slip.c:IfActionSubsystem"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["Slip.c:IfActionSubsystem1"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["Slip.c:Slip_est1"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 8,
	stackTotal: 8};
	 this.metricsArray.fcn["Slip.c:look1_pbinlcapw"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 40,
	stackTotal: 40};
	 this.metricsArray.fcn["Slip_initialize"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["Slip_step"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 76,
	stackTotal: 116};
	 this.metricsArray.fcn["byteswap-16.h:__bswap_16"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap-16.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_32"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["byteswap.h:__bswap_64"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\byteswap.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fabs"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fmax"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.getMetrics = function(token) { 
		 var data;
		 data = this.metricsArray.var[token];
		 if (!data) {
			 data = this.metricsArray.fcn[token];
			 if (data) data.type = "fcn";
		 } else { 
			 data.type = "var";
		 }
	 return data; }; 
	 this.codeMetricsSummary = '<a href="Slip_metrics.html">Global Memory: 8(bytes) Maximum Stack: 76(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
