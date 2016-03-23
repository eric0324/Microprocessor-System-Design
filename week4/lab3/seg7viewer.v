module seg7viewer(data_in, data_out);
input [7:0]data_in;
output [7:0]data_out;


assign data_out = seg7Decode(data_in);

function [7:0] seg7Decode;
input [7:0] num;
begin
	case(num)
		0 : seg7Decode = 8'b11000000;
		1 : seg7Decode = 8'b1111x001;
		2 : seg7Decode = 8'b10100100;
		3 : seg7Decode = 8'b1011?000;
		4 : seg7Decode = 8'b10011001;
		5 : seg7Decode = 8'b1001z011;
		6 : seg7Decode = 8'b10000010;
		7 : seg7Decode = 8'b11xxx000;
		8 : seg7Decode = 8'b10000000;
		9 : seg7Decode = 8'b10010000;
		default:
			seg7Decode = 8'b11111111;
	endcase
	end
endfunction
endmodule