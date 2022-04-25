function TraceInfoFlag() {
    this.traceFlag = new Array();
}
top.TraceInfoFlag.instance = new TraceInfoFlag();
function TraceInfoLineFlag() {
    this.lineTraceFlag = new Array();
    this.lineTraceFlag["Slip.c:86"]=1;
    this.lineTraceFlag["Slip.c:89"]=1;
}
top.TraceInfoLineFlag.instance = new TraceInfoLineFlag();
