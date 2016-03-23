module seg7viewer_tb_random();

reg [7:0]data_in;
wire [7:0]data_out;
integer RandomNum;

seg7viewer seg7viewer_inst(data_in,data_out);

initial begin
  data_in=0;
  
  #30 $finish;
end

always begin
  
  #2 RandomNum = {$random} % 9;
    data_in = RandomNum;

end
endmodule