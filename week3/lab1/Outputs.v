module outputs(sel, cnt_in, acc_in, men_in, seg7);

input [1:0]sel;
input [12:0] cnt_in, acc_in, men_in;
output [31:0] seg7;

reg[12:0] data;

seg7view seg_inst(data, seg7);

always@(sel) begin
	case(sel)
		0: data = cnt_in;
		1: data = acc_in;
		2: data = men_in;
	endcase
end

endmodule