package adapters;

import adapters.converting.ConvertingStrategy;
import model.MachineData;
import model.MachineDataModel;

/**
 * A MachineDataConverter converts a given MachineData's content to new model
 * it does so by using a converting strategy
 */
public class MachineDataConverter {
    private ConvertingStrategy convertingStrategy;

    /**
     * Given a MachineData object, attempts to return another with content in new model
     * if it is not possible to define a converting strategy, returns the original object
     * @param machineData
     * @return a MachineData in new model
     */
    public MachineData convertMachineDataToNewModel(MachineData machineData) {
        boolean couldDefineStrategy = defineConvertingStrategyByModel(machineData.getMachineDataModel());
        
        if(couldDefineStrategy) {
            String newContent = convertContentByDefinedStrategy(machineData.getMachineContent());
            return new MachineData(newContent);
        }
        
        return machineData;
    }

    /**
     * Defines which strategy is going to be used based on model
     * @param model
     * @return boolean stating if it was possible to determine a strategy
     */
    private boolean defineConvertingStrategyByModel(MachineDataModel model) {
        //Implemente aqui sua solução para esse método (este comentário pode ser apagado)

        return true; //Pode alterar essa linha se necessário (este comentário pode ser apagado)
    }

    /**
     * Delegate content convertion to ConvertingStrategy abstraction
     * @param content
     * @return a string containing the converted content
     */
    private String convertContentByDefinedStrategy(String content) {
        String convertedContent = convertingStrategy.convertContent(content);
        return convertedContent;
    }
}
