module seg7view(data_in, data_out);
input [15:0] data_in;
output [15:0] data_out;

assign data_out=numDecode(data_in);
	
function [15:0] numDecode;
input [15:0]value;
integer num;
begin
	integer n0, n1, n2, n3;	
	num = value;
	n2 = (num%100)/10;
	n3 = (num%10);
	numDecode[15:8] = seg7Decode(n2);
	numDecode[7:0] = seg7Decode(n3);
end
endfunction

function [7:0] seg7Decode;
input [31:0] num;
begin
	case(num)
		0 : seg7Decode = 8'b11000000;
		1 : seg7Decode = 8'b11111001;
		2 : seg7Decode = 8'b10100100;
		3 : seg7Decode = 8'b10110000;
		4 : seg7Decode = 8'b10011001;
		5 : seg7Decode = 8'b10010010;
		6 : seg7Decode = 8'b10000010;
		7 : seg7Decode = 8'b11011000;
		8 : seg7Decode = 8'b10000000;
		9 : seg7Decode = 8'b10010000;
		default :
			 seg7Decode = 8'b11111111;
	endcase
end
endfunction

endmodule
