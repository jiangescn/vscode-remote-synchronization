# @author Julie Zelenski
# 这会设置 Makefile 的默认目标，使
# 不带参数的 make 会触发 make install。
# 用于复制 staticlib 和头文件
# 安装位置信息，而无需学生
# 选择 install 目标。

.DEFAULT_GOAL = assume_install

assume_install: message install

message:
	@echo "NOTE: Library project assuming install target"
