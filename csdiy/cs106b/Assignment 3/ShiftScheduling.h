#ifndef ShiftScheduling_Included
#define ShiftScheduling_Included

#include "Shift.h"
#include "set.h"

/**
 * 给定兼职员工可选择的潜在班次集合、允许工作小时数
 * 该员工允许工作的时间，以及一周中每个班次的估计价值，
 * 返回使该员工产生价值最大的班次集合。
 *
 * 可以假定允许员工工作的小时数非负，
 * 但它可能为零（例如该员工当周休假。）
 *
 * 不允许安排员工在重叠的班次工作。例如，
 * 选择周一 8:00AM - 4:00PM 班次的员工不能同时选择 2:00PM - 6:00PM
 * 班次。
 *
 * 某些班次的价值可能为零甚至负数，这可能
 * 例如，如果支付员工完成工作的成本低于
 * 预计带来的收入。
 *
 * 如果多个不同日程并列且都能产生相同的
 * 值时，可以返回其中任意一个日程。
 *
 * 不要求用完员工所有可用工时。
 *
 * maxHours 可以为零，但不能为负数。如果客户端传入负数
 * maxHours 的值，应使用 error() 函数报告错误。
 *
 * @param shifts 所有可能分配的班次。
 * @param maxHours 员工允许工作的最大小时数。
 * @return 使带来价值最大化的工人排班表。该排班表不能
 *         不能有重叠班次，也不能超过最大工作小时数。
 */
Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours);

#endif
