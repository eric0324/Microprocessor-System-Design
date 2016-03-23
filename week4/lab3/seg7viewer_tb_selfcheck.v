module seg7viewer_tb_selfcheck();

reg [7:0]data_in;
wire [7:0]data_out;
integer RandomNum;


seg7viewer seg7viewer_inst(data_in,data_out);

initial begin
  data_in=0;
  
  #35 $finish;
end

always begin
    
  #2 RandomNum = {$random} % 9;
    data_in = RandomNum;
    case (data_out)
      8'b11000000:
        $display("0");
      8'b11111001:
        $display("1");
      8'b10100100:
        $display("2");
      8'b10110000:
        $display("3");
      8'b10011001:
        $display("4");
      8'b10010010:
        $display("5");
      8'b10000010:
        $display("6");
      8'b11011000:
        $display("7");
      8'b10000000:
        $display("8");
      8'b10010000:
        $display("9");
      default:begin
        $display("Error at $g", $time);
        $finish;
      end
        
    endcase
   
end
endmodule