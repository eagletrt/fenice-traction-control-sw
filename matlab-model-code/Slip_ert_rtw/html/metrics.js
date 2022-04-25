function CodeMetrics() {
	 this.metricsArray = {};
	 this.metricsArray.var = new Array();
	 this.metricsArray.fcn = new Array();
	 this.metricsArray.fcn["Slip_initialize"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
	stack: 0,
	stackTotal: 0};
	 this.metricsArray.fcn["Slip_step"] = {file: "C:\\Users\\dalle\\Desktop\\Formula SAE\\Vehicle model & controls 2022\\Slip_ert_rtw\\Slip.c",
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
	 this.codeMetricsSummary = '<a href="Slip_metrics.html">Global Memory: 0(bytes) Maximum Stack: 0(bytes)</a>';
	}
CodeMetrics.instance = new CodeMetrics();
