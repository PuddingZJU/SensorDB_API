#zhangxaochen:
pySensordb.cpp
	�� cpp �����ݿ�ӿڱ�¶Ϊ C �ӿ�

sensordb.py
	��ctypes��dll�������ð�װΪpython�࣬ʹ����cpp������ݿ�ӿڷ��һ��

test_sensordb.py
	���ݿ�ӿ�ʹ�ò��ԣ�
	����1��	ctypes ֱ�ӵ���dll��������
	����2��	ʹ��SensorDB��װ��

python�¿��� nose ���ԣ�
cmake �������̣� 
SensorDB_API_shared ��Ϊ�����
���� SensorDB_API.dll, ���俽���� <xxx>\SensorDB_API\src ��
�ڵ�ǰ·�������� cmd�� ���� nosetests�� ���˳�����������������
��
	.
	-----------------------------------------------------------------
	Ran 2 tests in 16.567s
	OK
��