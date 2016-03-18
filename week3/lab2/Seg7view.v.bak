module seg7view(data_in, data_out);
input [9:0] data_in;
output [31:0] data_out;

assign data_out=numDecode(data_in);
	
function [31:0] numDecode;
input [12:0]value;
integer num;
begin
	integer n0, n1, n2, n3;	
	num = value;
	n0 = num/1000;
	n1 = (num%1000)/100;
	n2 = (num%100)/10;
	n3 = (num%10);
	numDecode[31:24] = seg7Decode(n0);
	numDecode[23:16] = seg7Decode(n1);
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
