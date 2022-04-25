function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Torque.c:look1_binlxpw"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Torque_ert_rtw\\Torque.c",
	stack: 28,
	stackTotal: 28};
	 this.metricsArray.fcn["Torque_initialize"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Torque_ert_rtw\\Torque.c",
	stack: 4,
	stackTotal: 4};
	 this.metricsArray.fcn["Torque_step"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Torque_ert_rtw\\Torque.c",
	stack: 60,
	stackTotal: 88};
	 this.metricsArray.fcn["atan"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
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
	 this.metricsArray.fcn["fmin"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["fmod"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["memset"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\string.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["pow"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["tan"] = {file: "C:\\Program Files\\MATLAB\\R2021a\\polyspace\\verifier\\cxx\\include\\include-libc\\bits\\mathcalls.h",
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
	 this.codeMetricsSummary = '<a href="Torque_metrics.html">Global Memory: 0(bytes) Maximum Stack: 60(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
