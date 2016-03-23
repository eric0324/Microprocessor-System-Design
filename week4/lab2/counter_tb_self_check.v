module counter_tb_selfcheck();

reg clk,rst,en;
wire [9:0] counter_out;

counter counter_inst(clk, rst ,en , counter_out);

reg [9:0] old_value;

initial begin
  clk = 0;
  rst = 1;
  en = 1;
  
  #2 rst = 0;
  #200 rst = 0;
  #200 en = 1;
end

initial begin: RAND_CASE
  fork
    repeat (20) begin
      @(negedge clk);
      rst = $random;
    end
    repeat (40) begin
      @(negedge clk);
      en = $random;
    end
  join
end

always begin
  #5 clk = !clk;
end

always@(negedge clk) begin
  if(rst)begin
    if(counter_out != 0) begin
      $display("Reset Error Time %g", $time);
      $finish;
    end
  end else if (!en) begin
    if(counter_out != old_value) begin
      $display("Enable Error Time %g", $time);
      $finish;
    end
  end if(!rst && en) begin
    if(counter_out != old_value+1)begin
      $display("Counting Error Time %g", $time);
      $finish;
    end
  end 
  
  old_value = counter_out;
end
endmodule