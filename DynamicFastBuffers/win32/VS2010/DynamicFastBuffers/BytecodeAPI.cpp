#include <iostream>
#include "BytecodeAPI.h"

using namespace std;

namespace DynamicFastBuffers
{
	Bytecode* BytecodeAPI::generateBytecode(Typecode *typecode, flag flag)
	{
		if(typecode == NULL){
			throw WrongParamException("Parameter inserted is null. A Typecode object must be specified.");
		}
		void *index = NULL;
		Bytecode *bytecode = new Bytecode();
		if(flag){
			BytecodeAPI::generateBytecodeSerialization(bytecode, typecode, index);
		}else{
			BytecodeAPI::generateBytecodeDeserialization(bytecode, typecode, index);
		}
		return bytecode;
	}

	void BytecodeAPI::generateBytecodeSerialization(Bytecode *bytecode, Typecode *typecode, void *&index)
	{
		switch(typecode->getKind())
		{
		case TC_NOTYPE:
			//Do nothing
			break;
		case TC_INTEGER:
			bytecode->addFunction(SerializerAPI::serializeInteger);
			break;
		case TC_SHORT:
			bytecode->addFunction(SerializerAPI::serializeShort);
			break;
		case TC_LONG:
			bytecode->addFunction(SerializerAPI::serializeLong);
			break;
		case TC_FLOAT:
			bytecode->addFunction(SerializerAPI::serializeFloat);
			break;
		case TC_DOUBLE:
			bytecode->addFunction(SerializerAPI::serializeDouble);
			break;
		case TC_STRING:
			bytecode->addFunction(SerializerAPI::serializeString);
			break;
		case TC_CHARACTER:
			bytecode->addFunction(SerializerAPI::serializeCharacter);
			break;
		case TC_BOOLEAN:
			bytecode->addFunction(SerializerAPI::serializeBoolean);
			break;
		case TC_STRUCT:
			{
				vector<Typecode> members = typecode->getMembers();
				insertJumps(typecode, bytecode, index);
				size_t count = members.size();
				bool jumped = false;
				for(int i=0; i<count; ++i){
					//if(i != count){
					if(members[i].getKind() == TC_STRUCT){
						generateBytecodeSerialization(bytecode, &members[i], index);
						//if define(_M_IX86)
						if(((int) index % 8) != 0){
							//index = (char*) index + (8 - ((int) index % 8));
							Typecode* jumper = new Typecode(TC_DOUBLE);
							insertJumps(jumper, bytecode, index);
							delete(jumper);
							jumped = true;
						}
						//endif
					}else{
						if(i==0 || jumped){
							alignment(members[i].getSize(), index);
							jumped = false;
						}else{
							insertJumps(&members[i], bytecode, index);
						}
						generateBytecodeSerialization(bytecode, &members[i], index);
						index = (char*) index + (members[i].getSize()*members[i].getArraySize());
					}
				}
				//if define(_M_IX86)
				/*if(((int) index % 8) != 0){
					index = (char*) index + sizeof(int);
				}*/
				//endif
			}
			break;
		//case TC_UNION:
		case TC_ARRAY:
			{
				int nDims = typecode->getConstentSize();
				vector<int> dimensions = typecode->getDimensions();
				int serializations = 1;
				int i=0;
				for(i; i<nDims; ++i){
					int dim = dimensions[i];
					serializations *= dim;
				}
				bytecode->setSize(serializations);
				switch(typecode->getType()->getKind())
				{
				case TC_INTEGER:
					bytecode->addFunction(SerializerAPI::serializeArrayInteger);
					break;
				case TC_SHORT:
					bytecode->addFunction(SerializerAPI::serializeArrayShort);
					break;
				case TC_LONG:
					bytecode->addFunction(SerializerAPI::serializeArrayLong);
					break;
				case TC_FLOAT:
					bytecode->addFunction(SerializerAPI::serializeArrayFloat);
					break;
				case TC_DOUBLE:
					bytecode->addFunction(SerializerAPI::serializeArrayDouble);
					break;
				case TC_STRING:
					// Not supported
					break;
				case TC_CHARACTER:
					bytecode->addFunction(SerializerAPI::serializeArrayCharacter);
					break;
				case TC_BOOLEAN:
					// Not supported
					break;
				}
				break;
			}
		case TC_SEQUENCE:
			{
				switch(typecode->getType()->getKind())
				{
				case TC_INTEGER:
					bytecode->addFunction(SerializerAPI::serializeSequenceInteger);
					break;
				case TC_SHORT:
					bytecode->addFunction(SerializerAPI::serializeSequenceShort);
					break;
				case TC_LONG:
					bytecode->addFunction(SerializerAPI::serializeSequenceLong);
					break;
				case TC_FLOAT:
					bytecode->addFunction(SerializerAPI::serializeSequenceFloat);
					break;
				case TC_DOUBLE:
					bytecode->addFunction(SerializerAPI::serializeSequenceDouble);
					break;
				case TC_STRING:
					//Not supported
					break;
				case TC_CHARACTER:
					bytecode->addFunction(SerializerAPI::serializeSequenceCharacter);
					break;
				case TC_BOOLEAN:
					//Not supported
					break;
				}
			}
		}
	}

	void BytecodeAPI::generateBytecodeDeserialization(Bytecode *bytecode, Typecode *typecode, void *&index)
	{
		switch(typecode->getKind())
		{
		case TC_NOTYPE:
			//Do nothing
			break;
		case TC_INTEGER:
			bytecode->addFunction(SerializerAPI::deserializeInteger);
			break;
		case TC_SHORT:
			bytecode->addFunction(SerializerAPI::deserializeShort);
			break;
		case TC_LONG:
			bytecode->addFunction(SerializerAPI::deserializeLong);
			break;
		case TC_FLOAT:
			bytecode->addFunction(SerializerAPI::deserializeFloat);
			break;
		case TC_DOUBLE:
			bytecode->addFunction(SerializerAPI::deserializeDouble);
			break;
		case TC_STRING:
			bytecode->addFunction(SerializerAPI::deserializeString);
			break;
		case TC_CHARACTER:
			bytecode->addFunction(SerializerAPI::deserializeCharacter);
			break;
		case TC_BOOLEAN:
			bytecode->addFunction(SerializerAPI::deserializeBoolean);
			break;
		case TC_STRUCT:
			{
				vector<Typecode> members = typecode->getMembers();
				insertJumps(typecode, bytecode, index);
				size_t count = members.size();
				bool jumped = false;
				for(int i=0; i<count; ++i){
					if(members[i].getKind() == TC_STRUCT){
						generateBytecodeDeserialization(bytecode, &members[i], index);
						//if define(_M_IX86)
						if(((int) index % 8) != 0){
							//index = (char*) index + (8 - ((int) index % 8));
							Typecode* jumper = new Typecode(TC_DOUBLE);
							insertJumps(jumper, bytecode, index);
							delete(jumper);
							jumped = true;
						}
						//endif
					}else{
						if(i==0 || jumped){
							alignment(members[i].getSize(), index);
							jumped = false;
						}else{
							insertJumps(&members[i], bytecode, index);
						}
						generateBytecodeDeserialization(bytecode, &members[i], index);
						index = (char*) index + (members[i].getSize()*members[i].getArraySize());
					}
				}
				//if define(_M_IX86)
				/*if(((int) index % 8) != 0){
					index = (char*) index + sizeof(int);
				}*/
				//endif
				break;
			}
		//case TC_UNION:
		case TC_ARRAY:
			{
				int nDims = typecode->getConstentSize();
				vector<int> dimensions = typecode->getDimensions();
				int serializations = 1;
				int i=0;
				for(i; i<nDims; ++i){
					int dim = dimensions[i];
					serializations *= dim;
				}
				bytecode->setSize(serializations);
				switch(typecode->getType()->getKind())
				{
				case TC_INTEGER:
					bytecode->addFunction(SerializerAPI::deserializeArrayInteger);
					break;
				case TC_SHORT:
					bytecode->addFunction(SerializerAPI::deserializeArrayShort);
					break;
				case TC_LONG:
					bytecode->addFunction(SerializerAPI::deserializeArrayLong);
					break;
				case TC_FLOAT:
					bytecode->addFunction(SerializerAPI::deserializeArrayFloat);
					break;
				case TC_DOUBLE:
					bytecode->addFunction(SerializerAPI::deserializeArrayDouble);
					break;
				case TC_STRING:
					//Not supported
					break;
				case TC_CHARACTER:
					bytecode->addFunction(SerializerAPI::deserializeArrayCharacter);
					break;
				case TC_BOOLEAN:
					//Not supported
					break;
				}
				break;
			}
		case TC_SEQUENCE:
			{
				switch(typecode->getType()->getKind())
				{
				case TC_INTEGER:
					bytecode->addFunction(SerializerAPI::deserializeSequenceInteger);
					break;
				case TC_SHORT:
					bytecode->addFunction(SerializerAPI::deserializeSequenceShort);
					break;
				case TC_LONG:
					bytecode->addFunction(SerializerAPI::deserializeSequenceLong);
					break;
				case TC_FLOAT:
					bytecode->addFunction(SerializerAPI::deserializeSequenceFloat);
					break;
				case TC_DOUBLE:
					bytecode->addFunction(SerializerAPI::deserializeSequenceDouble);
					break;
				case TC_STRING:
					//Not supported
					break;
				case TC_CHARACTER:
					bytecode->addFunction(SerializerAPI::deserializeSequenceCharacter);
					break;
				case TC_BOOLEAN:
					//Not supported
					break;
				}
			}
		}
	}

	void BytecodeAPI::insertJumps(Typecode *typecode, Bytecode *bytecode, void *&m_currentPosition)
	{

		bytecode->addAlignment(alignment(typecode->getSize(), m_currentPosition));
#if defined(_M_IX86)
		if(typecode->getKind() == TC_STRING){
			m_currentPosition = (char*) m_currentPosition + sizeof(int);
		}
#endif
	}

	inline size_t BytecodeAPI::alignment(size_t dataSize, void *&m_currentPosition)
	{
		size_t align = (dataSize - ((int) m_currentPosition % dataSize)) & (dataSize-1);
		m_currentPosition = (char*) m_currentPosition + align;
		if(dataSize == 8 && (((int) m_currentPosition % 8) != 0)){
			m_currentPosition = (char*) m_currentPosition + sizeof(int);
			align += sizeof(int);
		}
		return align;
	}
};

