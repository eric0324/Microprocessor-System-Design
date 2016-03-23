module seg7viewer_tb_one();

reg [7:0]data_in;
wire [7:0]data_out;

seg7viewer seg7viewer_inst(data_in,data_out);

initial begin
  #2 data_in = 0;
  #2 data_in = 1;
  #2 data_in = 2;
  #2 data_in = 3;
  #2 data_in = 4;
  #2 data_in = 5;
  #2 data_in = 6;
  #2 data_in = 7;
  #2 data_in = 8;
  #2 data_in = 9;
end
endmodule
